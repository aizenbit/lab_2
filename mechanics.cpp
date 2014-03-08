#include "mechanics.h"

Mechanics::Mechanics(QWidget *parent) :
    QWidget(parent)
{
    //значения по умолчанию взяты из методички
    d = 0.5;
    l = 0.651;
    n = 0;
    B = 0;

    array = new qreal*[3];
    for(int i = 0; i < 3; i++)
        array[i] = new qreal[14];

    setMinimumSize(400,400);
}

//---------------------------------------------------------

void Mechanics::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.begin(this);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);

    //рисуем координатные оси
    painter.drawLine(13, height() - 17, width() - 15, height() - 17);
    painter.drawLine(13, height() - 17, 13, 5);
    painter.drawText(5, height() - 5, "0");
    painter.drawText(0 ,13, "m");
    painter.drawText(width()-50, height()-5, "sin^2(α)");

    if(!pointList.isEmpty())
    {
        //рисуем точки графика, соединяем их линиями
        for(int i = 1; i < pointList.size(); i++)
        {
            painter.drawLine(pointList.at(i), pointList.at(i - 1));
            painter.drawEllipse(pointList.at(i - 1), 2, 2);
        }
        //рисуем линию тренда
        painter.setPen(Qt::blue);
        painter.drawLine(13, height() - 17, width(), -B * 0.25);
    }

    painter.end();
}

//---------------------------------------------------------

Mechanics::~Mechanics()
{
    for (int i = 0; i < 3; i++)
        delete[] array[i];
    delete[] array;
}

//---------------------------------------------------------

void Mechanics::graph()
{
    pointList.clear();
    //заполняем pointList данными из array, иначе говоря,
    //переводим данные из таблицы в точки графика
    for(int column = 0; column < 14; column++)
        {
            qreal m = array[0][column];
            qreal alpha = array[1][column] - array[2][column];
            if ((alpha > 0) && (alpha < 30) && (m > 0))
            {
                alpha = alpha / 180 * 3.14156535; //потому что sin() принимает радианы
                pointList << QPointF(sin(alpha) * sin(alpha), m);
            }
        }

    findN();


    if (!pointList.isEmpty())
    {
        //сортируем иксы пузырьком по возрастанию
        for(int i = 0; i < pointList.size() - 1; i++)
            for(int j = 0; j < pointList.size() - i; j++)
                if (pointList[i].rx() > pointList[i + 1].rx())
                    pointList.swap(i, i + 1);

        qreal maxM = pointList.last().ry();
        qreal maxSin = pointList.last().rx();
        //высота и ширина графика
        qreal height = this->height() - 17;
        qreal width = this->width();

        //преобразуем точки так, чтобы их можно было нарисовать
        //на ограниченной области графика(виджета Mechanics)
        for(int i = 0; i < pointList.size(); i++)
        {
            qreal x = pointList.value(i).rx();
            qreal y = pointList.value(i).ry();
            pointList[i].setX(13 + x / maxSin * width);
            pointList[i].setY(height - (y / maxM * height));
        }

        repaint();
    }
}


//---------------------------------------------------------

void Mechanics::findN()
{
    B = 0;
    for(int i = 1; i < pointList.size(); i++)
        B += pointList[i].ry() / pointList[i].rx();
    B /= pointList.size();
    n = d / B / l * 1000;
    emit nChanged(n);
}

//---------------------------------------------------------

qreal Mechanics::getD()
{
    return d;
}

//---------------------------------------------------------

qreal Mechanics::getL()
{
    return l;
}

//---------------------------------------------------------

void Mechanics::setD(qreal newD)
{
    if(newD > 0)
        d = newD;
    else
        emit err(wrongData);
}

//---------------------------------------------------------

void Mechanics::setL(qreal newL)
{
    if(newL > 0)
        l = newL;
    else
        emit err(wrongData);
}

//---------------------------------------------------------

void Mechanics::setDataToArray(int row, int column, qreal data)
{
    if (data >= 0)
        array[row][column] = data;
    else
        emit err(wrongData);
}

//---------------------------------------------------------

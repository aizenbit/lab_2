#include "mechanics.h"

Mechanics::Mechanics(QWidget *parent) :
    QWidget(parent)
{
    pointList = new QList<QPointF>;

    d = 0.5;
    l = 0.651;
    n = 0;

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
    painter.drawLine(13,height()-17,width()-15,height()-17);
    painter.drawLine(13,height()-17,13,5);
    painter.drawText(5,height()-5,"0");
    painter.drawText(0,13,"m");
    painter.drawText(width()-50,height()-5,"sin^2(α)");

    for(int i = 1; i < pointList->size(); i++)
        painter.drawLine(pointList->at(i), pointList->at(i-1));

    painter.end();
}

//---------------------------------------------------------

Mechanics::~Mechanics()
{
    delete pointList;

    for (int i = 0; i < 3; i++)
        delete[] array[i];
    delete[] array;
}

//---------------------------------------------------------

void Mechanics::graph()
{
    pointList->clear();
    for(int column = 0; column < 14; column++)
        {
            qreal m = array[0][column];
            qreal alpha = array[1][column] - array[2][column];
            if ((alpha > 0) && (alpha < 30))
            {
                alpha = alpha / 180 * 3.14156535; //потому что sin() принимает радианы
                *pointList << QPointF(m, sin(alpha) * sin(alpha));
            }
        }

    if (!pointList->isEmpty())
    {
        qreal maxM = pointList->last().rx();
        qreal height = this->height();
        qreal width = this->width();
        for(int i = 0; i < pointList->size(); i++)
        {
            qreal x = pointList->value(i).rx();
            qreal y = pointList->value(i).ry();
            pointList->value(i).setX(x / maxM * height);
            pointList->value(i).setY(y * width);
        }
        repaint();
    }
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

qreal Mechanics::getN()
{
    return n;
}

//---------------------------------------------------------

void Mechanics::setD(qreal newD)
{
    if(newD > 0)
        d = newD;
}

//---------------------------------------------------------

void Mechanics::setL(qreal newL)
{
    if(newL > 0)
        l = newL;
}

//---------------------------------------------------------

void Mechanics::setDataToArray(int row, int column, qreal data)
{
    if (data >= 0)
        array[row][column] = data;
}

//---------------------------------------------------------

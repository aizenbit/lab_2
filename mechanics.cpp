#include "mechanics.h"

Mechanics::Mechanics(QWidget *parent) :
    QWidget(parent)
{
    pointList = new QList<QPointF>;
    setMinimumSize(400,400);
}

//---------------------------------------------------------

void Mechanics::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.begin(this);
    painter.setPen(Qt::black);
    for(int i = 1; i < pointList->size(); i++)
        painter.drawLine(pointList->at(i), pointList->at(i-1));
    painter.end();
}

//---------------------------------------------------------

Mechanics::~Mechanics()
{
    delete pointList;
}

//---------------------------------------------------------

void Mechanics::graph(qreal **array)
{
    pointList->clear();
    for(int column = 0; column < 14; column++)
        if(array[0][column] && array[1][column] && array[2][column])
        {
            qreal m = array[0][column];
            qreal alpha = array[1][column] - array[2][column];
            if (alpha > 0)
                *pointList << QPointF(m, sin(alpha) * sin(alpha));
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

    for (int i = 0; i < 3; i++)
            delete[] array[i];
    delete[] array;
}

#include "mechanics.h"

Mechanics::Mechanics(QWidget *parent) :
    QWidget(parent)
{
    pointList = new QList<QPointF>;
    d = 0.5;
    l = 0.651;
    n = 0;
    fi0 = 0;
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
        if(array[0][column] && array[1][column])
        {
            qreal m = array[0][column];
            qreal alpha = fi0 - array[2][column];
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

    for (int i = 0; i < 2; i++)
            delete[] array[i];
    delete[] array;
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

qreal Mechanics::getFi0()
{
    return fi0;
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

void Mechanics::setFi0(qreal newFi0)
{
    if(newFi0 > 0)
        fi0 = newFi0;
}

//---------------------------------------------------------

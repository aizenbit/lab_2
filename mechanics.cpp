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
    int i = 1;
    while(i < pointList->size())
    {
        painter.drawLine(pointList->at(i),pointList->at(i-1));
        i++;
    }

    painter.end();
}

//---------------------------------------------------------

Mechanics::~Mechanics()
{
    delete pointList;
}

//---------------------------------------------------------

void Mechanics::graph(double **array)
{
    pointList->clear();
    for(int column = 0; column < 14; column++)
        if(!array[0][column] && !array[1][column] && !array[2][column])
        {
            qreal m = array[0][column];
            qreal alpha = array[1][column] - array[2][column];
            if (alpha > 0)
                *pointList << QPointF(m,sin(alpha)*sin(alpha));
        }
    repaint();
}

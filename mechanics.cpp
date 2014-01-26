#include "mechanics.h"

Mechanics::Mechanics(QWidget *parent) :
    QWidget(parent)
{
    setMinimumSize(400,400);
}

//---------------------------------------------------------

void Mechanics::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.begin(this);

    painter.drawText(10,10,"Тут будет график");

    painter.end();
}

//---------------------------------------------------------

Mechanics::~Mechanics()
{

}

//---------------------------------------------------------

void Mechanics::graph(double **array)
{

}

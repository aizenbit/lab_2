#ifndef MECHANICS_H
#define MECHANICS_H

#define Pi 3.1415926535

#include <QtGui>
#include "errorCodes.h"

class Mechanics : public QWidget
{
    Q_OBJECT

private:
    virtual void paintEvent(QPaintEvent *);
    QList<QPointF> pointList;
    qreal d, l, n, B, **array;
    void prepareToGraph();

public:
    Mechanics(QWidget *parent = 0);
    ~Mechanics();
    qreal getD();
    qreal getL();

signals:
    void nChanged(qreal);
    void err(int);

public slots:

    void findN();
    void setD(qreal newD);
    void setL(qreal newL);
    void setDataToArray(int row, int column, qreal data);

};

#endif // MECHANICS_H

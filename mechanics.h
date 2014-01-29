#ifndef MECHANICS_H
#define MECHANICS_H

#include <QtWidgets>

class Mechanics : public QWidget
{
    Q_OBJECT

private:
    virtual void paintEvent(QPaintEvent *);
    QList<QPointF> *pointList;
    qreal d, l, n, **array;

public:
    Mechanics(QWidget *parent = 0);
    ~Mechanics();
    qreal getD();
    qreal getL();
    qreal getN();

signals:

public slots:
    void graph();
    void setD(qreal newD);
    void setL(qreal newL);
    void setDataToArray(int row, int column, qreal data);

};

#endif // MECHANICS_H

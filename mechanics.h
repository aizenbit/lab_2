#ifndef MECHANICS_H
#define MECHANICS_H

#include <QtWidgets>

class Mechanics : public QWidget
{
    Q_OBJECT

private:
    virtual void paintEvent(QPaintEvent *);
    QList<QPointF> *pointList;
    qreal d, l, n, fi0;

public:
    Mechanics(QWidget *parent = 0);
    ~Mechanics();
    qreal getD();
    qreal getL();
    qreal getN();
    qreal getFi0();

signals:

public slots:
    void graph(qreal **array);
    void setD(qreal newD);
    void setL(qreal newL);
    void setFi0(qreal newFi0);

};

#endif // MECHANICS_H

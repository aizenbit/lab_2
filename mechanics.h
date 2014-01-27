#ifndef MECHANICS_H
#define MECHANICS_H

#include <QtWidgets>

class Mechanics : public QWidget
{
    Q_OBJECT

private:
    virtual void paintEvent(QPaintEvent *);
    QList<QPointF> *pointList;

public:
    Mechanics(QWidget *parent = 0);
    ~Mechanics();

signals:

public slots:
    void graph(qreal **array);

};

#endif // MECHANICS_H

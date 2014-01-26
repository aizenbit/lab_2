#ifndef MECHANICS_H
#define MECHANICS_H

#include <QtWidgets>

class Mechanics : public QWidget
{
    Q_OBJECT

private:
    virtual void paintEvent(QPaintEvent *);
    double **array;

public:
    Mechanics(QWidget *parent = 0);
    ~Mechanics();

signals:

public slots:
    void graph(double **array);

};

#endif // MECHANICS_H

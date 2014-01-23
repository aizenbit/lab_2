#ifndef MECHANICS_H
#define MECHANICS_H

#include <QtWidgets>

class Mechanics : public QWidget
{
    Q_OBJECT

private:
    virtual void paintEvent(QPaintEvent *);

public:
    Mechanics(QWidget *parent = 0);
    ~Mechanics();

signals:

public slots:

};

#endif // MECHANICS_H

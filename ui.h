#ifndef UI_H
#define UI_H

#include <QtWidgets>
#include "mechanics.h"

class UI : public QWidget
{
    Q_OBJECT

private:
    Mechanics *mechanics;
    QTableWidget *tableWidget;
    QLabel *dLabel, *lLabel, *nLabel, *fi0Label;
    QPushButton *graphButton, *browseButton;
    QHBoxLayout *mainLayout, *dLayout, *lLayout, *nLayout, *fi0Layout;
    QVBoxLayout *dataLayout;
    QDoubleSpinBox *dSpinBox, *lSpinBox, *fi0SpinBox;
    QLineEdit *nLineEdit;

public:
    UI(QWidget *parent = 0);
    ~UI();

signals:
    void graph(qreal **);

public slots:
    void prepareToGraph();
};

#endif // UI_H

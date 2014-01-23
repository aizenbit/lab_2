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
    QLabel *dLabel, *lLabel, *nLabel;
    QPushButton *graphButton, *browseButton;
    QHBoxLayout *mainLayout, *dLayout, *lLayout, *nLayout;
    QVBoxLayout *dataLayout;
    QDoubleSpinBox *dSpinBox, *lSpinBox;
    QLineEdit *nLineEdit;

public:
    UI(Mechanics *mech, QWidget *parent = 0);
    ~UI();
};

#endif // UI_H

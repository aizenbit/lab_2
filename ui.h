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
    UI(QWidget *parent = 0);
    ~UI();

signals:
    void graph(qreal **);

public slots:
    void prepareToGraph();
};

#endif // UI_H

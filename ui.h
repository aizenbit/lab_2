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
    QLabel *dLabel, *lLabel, *nLabel,*d2Label, *l2Label;
    QPushButton *graphButton, *browseButton, *aboutButton;
    QHBoxLayout *mainLayout, *dLayout, *lLayout, *nLayout;
    QVBoxLayout *dataLayout;
    QDoubleSpinBox *dSpinBox, *lSpinBox;
    QLineEdit *nLineEdit;
    void fileToTable(QByteArray &line, int row);
    void fileToSpinBox(QByteArray &line, int spinBox);

public:
    UI(QWidget *parent = 0);
    ~UI();

signals:
    void graph(qreal **);
    void dataFromTable(int, int, qreal);

public slots:
    void prepareToGraph(int,int);
    void browse();
    void setN(qreal n);
};

#endif // UI_H

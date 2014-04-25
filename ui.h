#ifndef UI_H
#define UI_H

#include <QtGui>
#include "errorCodes.h"
#include "mechanics.h"

class UI : public QWidget
{
    Q_OBJECT

enum TableRow {m, fi0, fi1};
enum SpinBoxType {d, l};

private:
    Mechanics *mechanics;
    QTableWidget *tableWidget;
    QLabel *dLabel, *lLabel, *nLabel,*d2Label, *l2Label;
    QPushButton *findNButton, *browseButton, *aboutButton;
    QHBoxLayout *dataLayout, *dLayout, *lLayout, *nLayout;
    QVBoxLayout *mainLayout;
    QDoubleSpinBox *dSpinBox, *lSpinBox;
    QLineEdit *nLineEdit;
    QMessageBox *aboutBox, *errorBox;
    void fileToTable(QByteArray &line, TableRow row);
    void fileToSpinBox(QByteArray &line, SpinBoxType type);

public:
    UI(QWidget *parent = 0);
    ~UI();

signals:
    void graph(qreal **);
    void dataFromTable(int, int, qreal);

public slots:
    void prepareDataFromTable(int,int);
    void browse();
    void setN(qreal newN);
    void error(int);
};

#endif // UI_H

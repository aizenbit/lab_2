#include "ui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Mechanics *mechanics = new Mechanics();
    UI ui(mechanics);
    ui.show();
    return a.exec();
}

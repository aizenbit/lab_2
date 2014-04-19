#include "ui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    UI ui;
    ui.show();
    return a.exec();
}

#include "ui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(QCoreApplication::applicationDirPath() + "/plugins");
    paths.append(QCoreApplication::applicationDirPath() + "/plugins/platforms");
    paths.append("platforms");
    QCoreApplication::setLibraryPaths(paths);
    //QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath() + "/plugins/platforms");
    QApplication a(argc, argv);
    /*QStringList list = QCoreApplication::libraryPaths();
    QLabel label;
    QString str = "";
    for (int i = 0;i<list.size();i++)
    {
        str += list.at(i) + "\n";
    }
    label.setText(str);
    label.show();*/
    UI ui;
    ui.show();
    return a.exec();
}

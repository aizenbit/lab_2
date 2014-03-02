#include "ui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(QCoreApplication::applicationDirPath() + "/plugins");
    QCoreApplication::setLibraryPaths(paths);

    QApplication a(argc, argv);
    UI ui;
    ui.show();
    return a.exec();
}

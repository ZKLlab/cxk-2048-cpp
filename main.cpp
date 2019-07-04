#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QFontDatabase::addApplicationFont(":/fonts/SourceSansPro-Semibold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/SourceHanSansCN-Medium.otf");

    w.setWindowFlags(Qt::Window);
    w.showFullScreen();
    w.show();

    return a.exec();
}

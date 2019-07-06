#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QString configPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir configDir(configPath);
    if (!configDir.exists())
        configDir.mkpath(configPath);

    QFontDatabase::addApplicationFont(":/fonts/SourceSansPro-Semibold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/WenQuanYiMicroHei.otf");

    w.setWindowFlags(Qt::Window);
    w.showFullScreen();
    w.show();

    return a.exec();
}

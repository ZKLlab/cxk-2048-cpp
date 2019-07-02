#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamedef.h"
#include "game2048.h"
#include "gamecontainerwidget.h"
#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    Game2048 *game;
    GameContainerWidget *gameContainer;
};

#endif // MAINWINDOW_H

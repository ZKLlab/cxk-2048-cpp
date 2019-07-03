#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamedef.h"
#include "gamecontainer.h"
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
    GameContainer *gameContainer;
};

#endif // MAINWINDOW_H

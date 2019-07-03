#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamedef.h"
#include "gamecontainer.h"
#include <QKeyEvent>
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
protected:
    void keyPressEvent(QKeyEvent *event) override;
private:
    Ui::MainWindow *ui;
    GameContainer *gameContainer;
signals:
public slots:
    void handleNewGameClicked();
    void handleScoreUpdated(int score);
    void handleBestScoreUpdated(int bestScore);
};

#endif // MAINWINDOW_H

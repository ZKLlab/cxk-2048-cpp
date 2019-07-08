#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamedef.h"
#include "gamecontainer.h"
#include <sstream>
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
    ~MainWindow() override;
protected:
    void keyPressEvent(QKeyEvent *event) override;
private:
    Ui::MainWindow *ui;
    GameContainer *gameContainer; 

signals:
public slots:
    void handleNewGameClicked();
    void handleRetractClicked();
    void handleEliminateRowClicked();
    void handleEliminateColClicked();
    void handleScoreUpdated(int score);
    void handleBestScoreUpdated(int bestScore);
    void handleSoundEffectsVolumeChanged(int value);
    void handleRankingListUpdated(const std::string &content);
};

#endif // MAINWINDOW_H

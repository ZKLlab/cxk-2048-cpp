#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamedef.h"
#include "gamecontainer.h"
#include <sstream>
#include <QCursor>
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
    void handleClosed();
    void handleNewGameClicked();
    void handleRetractClicked();
    void handleEliminateRowClicked();
    void handleEliminateColClicked();
    void handleScoreUpdated(int score);
    void handlePropRetractEnabled(bool value);
    void handleBestScoreUpdated(int bestScore);
    void handlePropEliminateRowEnabled(bool value);
    void handlePropEliminateColEnabled(bool value);
    void handleSoundEffectsVolumeChanged(int value);
    void handleRankingListUpdated(const std::string &content);
    void handleCurrentStatusUpdated(const std::string &content);
};

#endif // MAINWINDOW_H

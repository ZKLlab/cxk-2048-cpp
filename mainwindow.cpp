#include "mainwindow.h"
#include "ui_mainwindow.h"

const char buttonStyleSheet[] = "background: #8f7a66;color: white;border: none;border-radius: 3px;margin: 0;padding: 0 12px;font-size: 14px;height: 32px;";
const char buttonStyleSheetDisabled[] = "background: #bdbdbd;color: white;border: none;border-radius: 3px;margin: 0;padding: 0 12px;font-size: 14px;height: 32px;";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gameContainer(new GameContainer())
{
    ui->setupUi(this);

    ui->exitButton->setStyleSheet(buttonStyleSheet);
    ui->retractButton->setStyleSheet(buttonStyleSheetDisabled);
    ui->eliminateRowButton->setStyleSheet(buttonStyleSheetDisabled);
    ui->eliminateColButton->setStyleSheet(buttonStyleSheetDisabled);

    gameContainer->setParent(ui->centralWidget);
    gameContainer->setFixedSize(CONTAINER_WIDTH, CONTAINER_WIDTH);
    ui->horizontalLayout->insertWidget(2, gameContainer);
    ui->gameInfo->setFixedHeight(CONTAINER_WIDTH);

    // 事件
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(handleClosed()));
    connect(ui->newGameButton, SIGNAL(clicked()), this, SLOT(handleNewGameClicked()));
    connect(ui->retractButton, SIGNAL(clicked()), this, SLOT(handleRetractClicked()));
    connect(ui->eliminateRowButton, SIGNAL(clicked()), this, SLOT(handleEliminateRowClicked()));
    connect(ui->eliminateColButton, SIGNAL(clicked()), this, SLOT(handleEliminateColClicked()));
    connect(ui->soundEffectsVolumeSlider, SIGNAL(valueChanged(int)), this, SLOT(handleSoundEffectsVolumeChanged(int)));

    connect(gameContainer, SIGNAL(soundEffectsVolumeChanged(int)), this, SLOT(handleSoundEffectsVolumeChanged(int)));
    connect(gameContainer, SIGNAL(propRetractEnabled(bool)), this, SLOT(handlePropRetractEnabled(bool)));
    connect(gameContainer, SIGNAL(propEliminateRowEnabled(bool)), this, SLOT(handlePropEliminateRowEnabled(bool)));
    connect(gameContainer, SIGNAL(propEliminateColEnabled(bool)), this, SLOT(handlePropEliminateColEnabled(bool)));
    connect(gameContainer, SIGNAL(bestScoreUpdated(int)), this, SLOT(handleBestScoreUpdated(int)));
    connect(gameContainer, SIGNAL(scoreUpdated(int)), this, SLOT(handleScoreUpdated(int)));
    connect(gameContainer, SIGNAL(rankingListUpdated(const std::string &)), this, SLOT(handleRankingListUpdated(const std::string &)));
    connect(gameContainer, SIGNAL(currentStatusUpdated(const std::string &)), this, SLOT(handleCurrentStatusUpdated(const std::string &)));

    handleSoundEffectsVolumeChanged(QMessageBox::question(this, "欢迎", "要打开游戏声音吗？") == QMessageBox::Yes ? 80 : 0);
    gameContainer->startGame();
}

void MainWindow::handleClosed()
{

    close();
}

void MainWindow::handleNewGameClicked()
{
    gameContainer->newGame();
}

void MainWindow::handleRetractClicked()
{
    gameContainer->retract();
}


void MainWindow::handleEliminateRowClicked()
{
    gameContainer->eliminateRow();
}

void MainWindow::handleEliminateColClicked()
{
    gameContainer->eliminateCol();
}

void MainWindow::handleScoreUpdated(int score)
{
    std::ostringstream text;
    text << score;
    ui->score->setText(text.str().c_str());
}

void MainWindow::handleBestScoreUpdated(int score)
{
    std::ostringstream text;
    text << score;
    ui->bestScore->setText(text.str().c_str());
}

void MainWindow::handleRankingListUpdated(const std::string &content)
{
    ui->rankingList->setText(content.c_str());
}


void MainWindow::handleCurrentStatusUpdated(const std::string &content)
{
    ui->currentStatus->setText(content.c_str());
}

void MainWindow::handleSoundEffectsVolumeChanged(int value)
{
    std::ostringstream text;
    text << value << '%';
    ui->soundEffectsVolume->setText(text.str().c_str());
    if (ui->soundEffectsVolumeSlider->value() != value)
        ui->soundEffectsVolumeSlider->setValue(value);
    gameContainer->setSoundEffectsVolume(value / 100.0);
}

void MainWindow::handlePropRetractEnabled(bool value)
{
    ui->retractButton->setEnabled(value);
    ui->retractButton->setStyleSheet(value ? buttonStyleSheet : buttonStyleSheetDisabled);
}

void MainWindow::handlePropEliminateRowEnabled(bool value)
{
    ui->eliminateRowButton->setEnabled(value);
    ui->eliminateRowButton->setStyleSheet(value ? buttonStyleSheet : buttonStyleSheetDisabled);
}

void MainWindow::handlePropEliminateColEnabled(bool value)
{
    ui->eliminateColButton->setEnabled(value);
    ui->eliminateColButton->setStyleSheet(value ? buttonStyleSheet : buttonStyleSheetDisabled);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gameContainer;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_W:
    case Qt::Key_Up:
        gameContainer->move(MOVE_UP);
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        gameContainer->move(MOVE_LEFT);
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        gameContainer->move(MOVE_DOWN);
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        gameContainer->move(MOVE_RIGHT);
        break;
    default:
        return;
    }
}

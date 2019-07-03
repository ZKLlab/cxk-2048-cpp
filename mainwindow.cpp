#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gameContainer(new GameContainer)
{
    ui->setupUi(this);
    gameContainer->setParent(ui->centralWidget);
    gameContainer->setFixedSize(CONTAINER_WIDTH, CONTAINER_WIDTH);
    ui->horizontalLayout->insertWidget(2, gameContainer);
    ui->gameInfo->setFixedHeight(CONTAINER_WIDTH);

    connect(ui->newGameButton, SIGNAL(clicked()), this, SLOT(handleNewGameClicked()));
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(close()));
}

void MainWindow::handleNewGameClicked()
{
    gameContainer->newGame();
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
        // 下行用于测试
        gameContainer->generateRandomTile();
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        break;
    }
}

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
    ui->horizontalLayout->insertWidget(3, gameContainer);
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

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
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gameContainer;
}

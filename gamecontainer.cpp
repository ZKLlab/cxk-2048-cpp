#include "gamecontainer.h"

GameContainer::GameContainer(QWidget *parent) :
    QWidget(parent),
    score(0)
{

}

void GameContainer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    // 绘制背景
    painter.setBrush(QColor("#bbada0"));
    painter.drawRoundedRect(0, 0, CONTAINER_WIDTH, CONTAINER_WIDTH, 6, 6);
    // 绘制格子
    painter.setBrush(QColor(238, 228, 218, 90));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            painter.drawRoundedRect(j * TILE_WIDTH + (j + 1) * GUTTER_WIDTH, i * TILE_WIDTH + (i + 1) * GUTTER_WIDTH,
                                    TILE_WIDTH, TILE_WIDTH,
                                    3, 3);
        }
    }
}

void GameContainer::addTile(int value, int row, int col)
{
    tiles.emplace_back(value, row, col);
}

#include "gamecontainer.h"
#include <random>

GameContainer::GameContainer(QWidget *parent) :
    QWidget(parent),
    score(0)
{
    newGame();
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
    Tile &tile = tiles.back();
    tile.setParent(this);
    tile.setGeometry(tile.getX(), tile.getY(), TILE_WIDTH, TILE_WIDTH);
}

void GameContainer::generateRandomTile()
{
    auto matrix = getTilesMatrix();
    bool haveSpare = false;
    int spare[16][2], k = 0;
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 2; j++)
            spare[i][j] = -1;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (matrix[std::size_t(i)][std::size_t(j)] == nullptr)
            {
                spare[k][0] = i;
                spare[k][1] = j;
                k++;
                haveSpare = true;
            }
        }
    }
    if (!haveSpare)
        return;
    int a = 0, temp = 0;
    std::random_device rd;  // 将用于为随机数引擎获得种子
    std::mt19937 gen(rd()); // 以播种标准 mersenne_twister_engine
    std::uniform_int_distribution<> dis(0, k-1);
    a = dis(gen);
    std::uniform_int_distribution<> dis2(0, 9);
    temp = dis2(gen);
    if (temp <= 8)
    {
        addTile(2, spare[a][0], spare[a][1]);
    }
    else
    {
        addTile(4, spare[a][0], spare[a][1]);
    }
}

void GameContainer::newGame()
{
    tiles.clear();
    score = 0;
    generateRandomTile();
    generateRandomTile();
}

std::vector<std::vector<Tile *>> GameContainer::getTilesMatrix()
{
    std::vector<std::vector<Tile *>> matrix;
    matrix.resize(4);
    for (auto &row : matrix)
    {
        row = {nullptr, nullptr, nullptr, nullptr};
    }
    for (auto &tile : tiles)
    {
        matrix[std::size_t(tile.getRow())][std::size_t(tile.getCol())] = &tile;
    }
    return matrix;
}

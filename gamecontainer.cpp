#include "gamecontainer.h"

GameContainer::GameContainer(QWidget *parent) :
    QWidget(parent),
    score(0)
{
    addTile(2, 1, 1);
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
    // 以下测试
    tile.moveTo(2, 3);
    tile.doubleValue();
}

void GameContainer::generateRandomTile()
{

}

void GameContainer::newGame()
{

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
        matrix[tile.getRow()][tile.getCol()] = &tile;
    }
    return matrix;
}

int GameContainer::getScore() const
{
    return score;
}

void GameContainer::updateScore(int value)
{
    score += value;
}

std::string GameContainer::serialize()
{
    std::string information;
    std::ostringstream record(information);
    record << score;
    auto matrix = getTilesMatrix();
    for (auto &row : matrix)
    {
        for (Tile *tile : row)
        {
            record << " " << tile->getValueText();
        }
    }
    return information;
}

void GameContainer::deserialize(std::string information)
{
    std::istringstream read(information);
    read >> score;
    auto matrix = getTilesMatrix();
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            int value;
            read >> value;
            addTile(value, row, col);
        }
    }
}

void GameContainer::recordFile(std::string information)
{
    std::ofstream outfile("2048Record.txt", std::ios::trunc);
    outfile << information;
    outfile.close();
}

std::string GameContainer::readFile()
{
    std::string information;
    std::ifstream infile("2048Record.tet");
    infile >> information;
    infile.close();
    return information;
}

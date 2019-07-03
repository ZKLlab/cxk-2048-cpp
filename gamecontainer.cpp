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
    tile.show();
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
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<> dis(0, k - 1);
    int pos = dis(gen);
    std::uniform_int_distribution<> dis2(0, 9);
    int temp = dis2(gen);
    addTile((temp == 0 ? 4 : 2), spare[pos][0], spare[pos][1]);
}

void GameContainer::newGame()
{
    tiles.clear();
    score = 0;
    generateRandomTile();
    generateRandomTile();
    prop_flag = false;
    prop_elmcol = 0;
    prop_elmrow = 0;
    prop_retraction = 0;
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

void GameContainer::move()
{
    auto matrix = getTilesMatrix();
    bool isMoved = false;
        for(int col = 0; col < 4; col++)
        {
            for (int row = 1; row < 4; row++)
            {
                int r = row - 1;
                while(matrix[r][col] == nullptr && r > 0) --r;
                if (matrix[r][col]->getValue() == matrix[row][col]->getValue() && matrix[row][col] != nullptr)
                {
                    matrix[row][col]->moveTo(r, col);
                    matrix[r][col]->doubleValue();
                    updateScore(matrix[r][col] -> getValue());
                    isMoved = true;
                }
            }
            for (int row = 1; row < 4; row++)
            {
                for(int r = row; r >= 1; r--)
                {
                    if(matrix[r - 1][col] == nullptr && matrix[r][col] != nullptr )
                    {
                        matrix[r][col]->moveTo(r - 1, col);
                        isMoved = true;
                    }
                }
            }
        }
        if(isMoved)
        {
            generateRandomTile();
        }
}

int GameContainer::getScore() const
{
    return score;
}
void GameContainer::updateScore(int value)
{
    score += value;
}

std::string GameContainer::serialize()//保存当前游戏所有状态
{
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
    record << " " << prop_flag << " " << prop_elmcol << " " << prop_elmrow << " " << prop_retraction;
    return information;
}

std::string GameContainer::part_serialize()//保存除道具数量之外的状态
{
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

void GameContainer::deserialize()//复盘游戏所有状态
{
    std::istringstream read(information);
    read >> score;
    tiles.clear();
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            int value;
            read >> value;
            if (value > 0)
            {
                addTile(value, row, col);
            }
        }
    }
    read  >> prop_flag >> prop_elmcol >> prop_elmrow >> prop_retraction;
}

void GameContainer::part_deserialize()//复盘游戏除道具外所有状态
{
    std::istringstream read(information);
    read >> score;
    tiles.clear();
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            int value;
            read >> value;
            if (value > 0)
            {
                addTile(value, row, col);
            }
        }
    }
}

void GameContainer::recordFile()
{
    std::ofstream outfile("2048Record.txt", std::ios::trunc);
    outfile << information;
    outfile.close();
}

void GameContainer::readFile()
{
    std::ifstream infile("2048Record.txt");
    infile >> information;
    infile.close();
}

void GameContainer::elmcol()
{
    std::istringstream read(information);
    read >> score;
    tiles.clear();
    /*(int temp[4];
    for (int i = 0; i < 4; i++)
    {
        int value;
        read >> value;
        temp[i] += value;
        sort(temp, temp + 4);
    }*/
}

void GameContainer::retract()
{
    if (prop_flag == true)
    {
        part_deserialize();
        prop_flag = false;
    }
int GameContainer::getWinTile() const
{
    return winTile;
}

void GameContainer::setWinTile(int value)
{
   winTile = value;
}

int GameContainer::judge()
{
    auto matrix = getTilesMatrix();
    // 赢得游戏
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (matrix[row][col]->getValue() == winTile)
            {
                return GAME_WIN;
            }
        }
    }
    // 横向检查
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4 - 1; col++)
        {
            if (matrix[row][col] == nullptr || (matrix[row][col]->getValue() == matrix[row][col + 1]->getValue()))
            {
                return GAME_CONTINUE;
            }
        }
    }
    // 纵向检查
    for (int col = 0; col < 4; col++)
    {
        for (int row = 0; row < 4 - 1; row++)
        {
            if (matrix[row][col] == nullptr || (matrix[row][col]->getValue() == matrix[row + 1][col]->getValue()))
            {
                return GAME_CONTINUE;
            }
        }
    }
    // 不符合上述两种状况，游戏结束
    return GAME_LOSE;
}

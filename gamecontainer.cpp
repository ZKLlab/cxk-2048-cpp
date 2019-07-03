#include "gamecontainer.h"
#include <random>

GameContainer::GameContainer(QWidget *parent) :
    QWidget(parent),
    score(0),
    winTile(2048)
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
            painter.drawRoundedRect(j * TILE_WIDTH + (j + 1) * GUTTER_WIDTH, i * TILE_WIDTH + (i + 1) * GUTTER_WIDTH, TILE_WIDTH, TILE_WIDTH, 3, 3);
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
    static std::random_device rd;
    static std::default_random_engine gen(rd());
    std::uniform_int_distribution<> dis(0, k - 1);
    int pos = dis(gen);
    std::uniform_int_distribution<> dis2(0, 9);
    int temp = dis2(gen);
    addTile((temp == 0 ? 4 : 2), spare[pos][0], spare[pos][1]);
}

void GameContainer::newGame()
{
    playSoundEffect(2);
    tiles.clear();
    resetScore();
    generateRandomTile();
    generateRandomTile();
    propFlag = false;
    propElmcol = 0;
    propElmrow = 0;
    propRetraction = 0;
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
        if (matrix[std::size_t(tile.getRow())][std::size_t(tile.getCol())] == nullptr ||
                matrix[std::size_t(tile.getRow())][std::size_t(tile.getCol())]->getValue() < tile.getValue())
        {
            matrix[std::size_t(tile.getRow())][std::size_t(tile.getCol())] = &tile;
        }
    }
    return matrix;
}

void GameContainer::cleanTiles()
{
    auto matrix = getTilesMatrix();
    for (auto tile = tiles.begin(); tile != tiles.end();)
    {
        bool flag = false;
        for (auto &row : matrix)
            for (Tile *tile2 : row)
                if (tile2 != nullptr && (*tile).getValue() == tile2->getValue())
                    flag = true;
        if (flag)
            tile++;
        else
            tiles.erase(tile);
    }
}

void GameContainer::move()
{
    /*partSerialize();
    auto matrix = getTilesMatrix();
    //cleanTiles;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            int r = j - 1;
            while (matrix[j][r] == nullptr) r--;
            if (matrix[j][i] != nullptr && matrix[r][i] != nullptr && matrix[j][i]->getValue() == matrix[r][i]->getValue())
            {
                propFlag = true;
                //merge(j, i, r, i);
            }
        }
    }*/

}
/*void GameContainer::merge(int X, int Y, int targetX, int targetY)
{
    martix
}*/

int GameContainer::getScore() const
{
    return score;
}

void GameContainer::updateScore(int value)
{
    score += value;
    scoreUpdated(score);
}

void GameContainer::resetScore()
{
    score = 0;
    scoreUpdated(score);
}

std::string GameContainer::serialize()
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
    record << " " << propFlag << " " << propElmcol << " " << propElmrow << " " << propRetraction;
    return information;
}

std::string GameContainer::partSerialize()
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

void GameContainer::deserialize()
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
    read  >> propFlag >> propElmcol >> propElmrow >> propRetraction;
}

void GameContainer::partDeserialize()
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

void GameContainer::retract()
{
    if (propFlag == true)
    {
        partDeserialize();
        propFlag = false;
    }
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

void GameContainer::playSoundEffect(int value)
{
    if (value > 4096)
        value = 4096;
    std::ostringstream url;
    QSoundEffect *effect = new QSoundEffect();
    url << "qrc:/soundEffects/effect-" << value << ".wav";
    effect->setSource(QUrl(url.str().c_str()));
    effect->setLoopCount(1);
    effect->setVolume(0.8);
    effect->play();
}

void GameContainer::elmrow()
{
    auto matrix = getTilesMatrix();
    int maxRow = 0, maxSum = 0, sum = 0;
    for (int row = 0; row < 4; row ++)
    {
        for (int col = 0; col < 4; col ++)
        {
            if (matrix[row][col] == nullptr)
                continue;
            sum += matrix[row][col]->getValue();
        }
        if (sum > maxSum)
        {
            maxSum = sum;
        }
        maxRow = row;
        sum = 0;
    }
    for (auto tile = tiles.begin(); tile != tiles.end();)
    {
        if ((*tile).getRow() != maxRow)
            tile++;
        else
            tiles.erase(tile);
    }
}

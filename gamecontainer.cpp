#include "gamecontainer.h"

GameContainer::GameContainer(QWidget *parent) :
    QWidget(parent),
    score(0),
    highest(0),
    winTile(2048)
{}

GameContainer::~GameContainer()
{
    if (information == "")
    {
        return;
    }
    serialize();
    recordFile();
}

void GameContainer::startGame()
{
    readFile();
    if (information.empty())
    {
        newGame();
    }
    else
    {
        continueGame();
    }
}

void GameContainer::continueGame()
{
    deserialize();
    showRankingList();
    initHighest();
    playSoundEffect(2);
    generateRandomTile();
    generateRandomTile();
}

void GameContainer::newGame()
{
    showRankingList();
    initHighest();
    if (setName())
    {
        playSoundEffect(2);
        tiles.clear();
        resetScore();
        generateRandomTile();
        generateRandomTile();
        propFlag = false;
        propRetractionFlag = false;
        propEliminateCol = 0;
        propEliminateRow = 0;
    }
}

void GameContainer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    // 绘制背景
    painter.setBrush(QColor("#bbada0"));
    painter.drawRoundedRect(0, 0, CONTAINER_WIDTH, CONTAINER_WIDTH, CONTAINER_BORDER_RADIUS, CONTAINER_BORDER_RADIUS);
    // 绘制格子
    painter.setBrush(QColor(238, 228, 218, 90));
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            painter.drawRoundedRect(j * TILE_WIDTH + (j + 1) * GUTTER_WIDTH, i * TILE_WIDTH + (i + 1) * GUTTER_WIDTH, TILE_WIDTH, TILE_WIDTH, TILE_BORDER_RADIUS, TILE_BORDER_RADIUS);
}

void GameContainer::addTile(int value, int row, int col)
{
    tiles.emplace_back(value, row, col);
    Tile &tile = tiles.back();
    tile.setParent(this);
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
    static std::default_random_engine gen(std::time(nullptr));
    std::uniform_int_distribution<> dis(0, k - 1);
    int pos = dis(gen);
    std::uniform_int_distribution<> dis2(0, 9);
    int temp = dis2(gen);
    addTile((temp == 0 ? 4 : 2), spare[pos][0], spare[pos][1]);
}

std::vector<std::vector<Tile *>> GameContainer::getTilesMatrix()
{
    std::vector<std::vector<Tile *>> matrix;
    matrix.resize(4);
    for (auto &row : matrix)
        row = {nullptr, nullptr, nullptr, nullptr};
    for (auto &tile : tiles)
        if (matrix[std::size_t(tile.getRow())][std::size_t(tile.getCol())] == nullptr ||
                matrix[std::size_t(tile.getRow())][std::size_t(tile.getCol())]->getValue() < tile.getValue())
            matrix[std::size_t(tile.getRow())][std::size_t(tile.getCol())] = &tile;
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
                if (tile2 != nullptr &&
                        tile->getRow() == tile2->getRow() &&
                        tile->getCol() == tile2->getCol() &&
                        tile->getValue() == tile2->getValue())
                    flag = true;
        if (flag)
            tile++;
        else
            tile = tiles.erase(tile);
    }
}

void GameContainer::move(int direction)
{
    partSerialize();
    auto matrix = getTilesMatrix();
    cleanTiles();
    bool isMoved = false;
    int maxMergedTile = 0;
    std::vector<std::vector<int>> base;
    std::vector<std::vector<int>> diff;
    switch (direction)
    {
    case MOVE_UP:
        base = {{0, 0}, {0, 1}, {0, 2}, {0, 3}};
        diff = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
        break;
    case MOVE_LEFT:
        base = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
        diff = {{0, 0}, {0, 1}, {0, 2}, {0, 3}};
        break;
    case MOVE_DOWN:
        base = {{3, 0}, {3, 1}, {3, 2}, {3, 3}};
        diff = {{0, 0}, {-1, 0}, {-2, 0}, {-3, 0}};
        break;
    case MOVE_RIGHT:
        base = {{0, 3}, {1, 3}, {2, 3}, {3, 3}};
        diff = {{0, 0}, {0, -1}, {0, -2}, {0, -3}};
        break;
    default:
        return;
    }
    for (std::vector<int> &basePos : base)
    {
        Tile *currentTile = nullptr;
        auto diffIter = diff.begin(); // 迭代器语法
        for (std::vector<int> &diffPos : diff)
        {
            int i = basePos[0] + diffPos[0], j = basePos[1] + diffPos[1];
            if (matrix[i][j] != nullptr)
            {
                if (currentTile != nullptr && matrix[i][j]->getValue() == currentTile->getValue())
                {
                    isMoved = true;
                    matrix[i][j]->moveToAndDoubleValue(currentTile->getRow(), currentTile->getCol());
                    updateScore(matrix[i][j]->getValue());
                    maxMergedTile = maxMergedTile > matrix[i][j]->getValue() ? maxMergedTile : matrix[i][j]->getValue();
                    currentTile = nullptr;
                }
                else
                {
                    int targetPosI = basePos[0] + (*diffIter)[0], targetPosJ = basePos[1] + (*diffIter)[1];
                    if (i != targetPosI || j != targetPosJ)
                    {
                        isMoved = true;
                        matrix[i][j]->moveTo(targetPosI, targetPosJ);
                    }
                    currentTile = matrix[i][j];
                    diffIter++;
                }
            }
        }
    }
    if (isMoved)
    {
        propFlag = true;
        propRetractionFlag = true;
        updateInformation();
        generateRandomTile();
        judge();
    }
    if (maxMergedTile > 2)
    {
        playSoundEffect(maxMergedTile);
    }
}

int GameContainer::getScore() const
{
    return score;
}

void GameContainer::updateScore(int value)
{
    score += value;
    scoreUpdated(score);
    setHighest();
}

void GameContainer::resetScore()
{
    score = 0;
    scoreUpdated(score);
}

std::string GameContainer::serialize()
{
    std::ostringstream record;
    record << score << " " << name;
    auto matrix = getTilesMatrix();
    for (auto &row : matrix)
    {
        for (Tile *tile : row)
        {
            if (tile != nullptr)
                record << " " << tile->getValueText();
            else
                record << " " << 0;
        }
    }
    record << " " << propFlag << " " << propEliminateCol << " " << propEliminateRow;
    information = record.str();
    return information;
}

std::string GameContainer::partSerialize()
{
    std::ostringstream record;
    record << score;
    auto matrix = getTilesMatrix();
    for (auto &row : matrix)
    {
        for (Tile *tile : row)
        {
            if (tile != nullptr)
                record << " " << tile->getValueText();
            else
                record << " " << 0;
        }
    }
    tempInformation = record.str();
    return tempInformation;
}

void GameContainer::deserialize()
{
    std::istringstream read(information);
    read >> score;
    read >> name;
    scoreUpdated(score);    // 给主界面发送分数修改信号
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
    read  >> propFlag >> propEliminateCol >> propEliminateRow;
}

void GameContainer::partDeserialize()
{
    std::istringstream read(information);
    read >> score;
    scoreUpdated(score);    // 给主界面发送分数修改信号
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

void GameContainer::updateInformation()
{
    information = tempInformation;
}

void GameContainer::recordFile()
{
    std::ofstream outfile(QDir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).filePath("2048Record.txt").toStdString(), std::ios::trunc);
    outfile << information;
    std::cout << information << std::endl;
    outfile.close();
}

std::string GameContainer::readFile()
{
    std::ifstream infile(QDir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).filePath("2048Record.txt").toStdString());
    getline(infile, information);
    if (infile.fail())
    {
        information = "";
    }
    infile.close();
    return information;
}

void GameContainer::retract()
{
    if (propRetractionFlag)
    {
        partDeserialize();
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
            if (matrix[row][col] != nullptr && matrix[row][col]->getValue() == winTile)
            {
                recordScore(score, name);
                showRankingList();
                saveHighest();
                clearFile();
                return GAME_WIN;
            }
        }
    }
    // 横向检查
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4 - 1; col++)
        {
            if (matrix[row][col] == nullptr || matrix[row][col + 1] == nullptr || (matrix[row][col]->getValue() == matrix[row][col + 1]->getValue()))
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
            if (matrix[row][col] == nullptr || matrix[row + 1][col] == nullptr  || (matrix[row][col]->getValue() == matrix[row + 1][col]->getValue()))
            {
                return GAME_CONTINUE;
            }
        }
    }
    // 不符合上述两种状况，游戏结束
    propRetractionFlag = false;
    recordScore(score, name);
    showRankingList();
    saveHighest();
    clearFile();
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
    effect->setVolume(soundEffectsVolume);
    effect->play();
}

void GameContainer::eliminateRow()
{
    if (propFlag)
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
                maxRow = row;
            }
            sum = 0;
        }
        for (auto tile = tiles.begin(); tile != tiles.end();)
        {
            if (tile->getRow() != maxRow)
                tile++;
            else
                tile = tiles.erase(tile);
        }
    }
    propFlag = false;
    propRetractionFlag = false;
}

void GameContainer::eliminateCol()
{
    if (propFlag)
    {
        auto matrix = getTilesMatrix();
        int maxCol = 0, maxSum = 0, sum = 0;
        for (int col = 0; col < 4; col ++)
        {
            for (int row = 0; row < 4; row ++)
            {
                if (matrix[row][col] == nullptr)
                    continue;
                sum += matrix[row][col]->getValue();
            }
            if (sum > maxSum)
            {
                maxSum = sum;
                maxCol = col;
            }
            sum = 0;
        }
        for (auto tile = tiles.begin(); tile != tiles.end();)
        {
            if (tile->getCol() != maxCol)
                tile++;
            else
                tile = tiles.erase(tile);
        }
    }
    propFlag = false;
    propRetractionFlag = false;
}

void GameContainer::recordScore(int scoreThis, std::string nameThis)
{
    std::clog << scoreThis << "  " << nameThis << std::endl;
    std::string line;
    int x;
    std::string y;
    std::ifstream infile(QDir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).filePath("RankingList.txt").toStdString());
    scoreList.clear();
    nameList.clear();
    while (getline(infile, line))
    {
        std::istringstream items(line);
        items >> x;
        if (!items.fail())
        {
            scoreList.push_back(x);
            std::ws(items);
            //items >> y;
            getline(items, y);
            nameList.push_back(y);
        }
    }
    scoreList.push_back(scoreThis);
    nameList.push_back(nameThis);
    for (size_t i = 0; i < scoreList.size(); i++)
    {
        for(size_t j = i; j < scoreList.size(); j++)
        {
            if (scoreList[i] < scoreList[j])
            {
                std::swap(scoreList[i], scoreList[j]);
                std::swap(nameList[i], nameList[j]);
            }
        }
    }
    infile.close();
    std::ofstream outfile(QDir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).filePath("RankingList.txt").toStdString(), std::ios::trunc);
    for (std::size_t j = 0; j < scoreList.size(); j++)
    {
        outfile << scoreList[j] << '\t' << nameList[j] << std::endl;
        std::cout << scoreList[j] << '\t' << nameList[j] << std::endl;
    }
    outfile.close();
}

void GameContainer::setHighest()
{
    highest = score > highest ? score : highest;
    //highest = score;
    //if (scoreList[0] > highest)
    //{
    //    highest = scoreList[0];
    //}
    bestScoreUpdated(highest);
}

void GameContainer::setSoundEffectsVolume(double value)
{
    soundEffectsVolume = value;
}

bool GameContainer::setName()
{
    bool ok;
    QString text;
    while (text == "")
    {
        text = QInputDialog::getText(this, "报上名来！", "请输入昵称：", QLineEdit::Normal, "", &ok);
        if (!ok)
            return false;
        text = text.trimmed();
    }
    name = text.toStdString();
    return true;
}

void GameContainer::initHighest()
{
    std::ifstream infile(QDir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).filePath("HighestScore.txt").toStdString());
    int i;
    infile >> i;
    if (infile.fail())
    {
        i = 0;
    }
    highest = i;
    infile.close();
}

void GameContainer::saveHighest()
{
    std::ifstream infile(QDir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).filePath("HighestScore.txt").toStdString());
    int i;
    infile >> i;
    if (infile.fail())
    {
        i = 0;
    }
    infile.close();
    highest = highest > i ? highest : i;
    std::ofstream outfile(QDir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).filePath("HighestScore.txt").toStdString(), std::ios::trunc);
    outfile << highest;
    outfile.close();
}

void GameContainer::showRankingList()
{
    std::ostringstream items;
    for (std::size_t i = 0, len = scoreList.size() >= 5 ? 5 : scoreList.size(); i < len; i++)
    {
        items << "#" << i + 1 << "   " << nameList[i] << "   " << scoreList[i] << std::endl;
    }
    rankingListUpdated(items.str());
}

void GameContainer::clearFile()
{
    information = "";
    std::ofstream outfile(QDir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).filePath("2048Record.txt").toStdString(), std::ios::trunc);
    outfile.close();
}

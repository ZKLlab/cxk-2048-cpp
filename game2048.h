#ifndef GAME2048_H
#define GAME2048_H

#include "gamedef.h"
#include "tile.h"
#include <list>

class Game2048
{
public:
    Game2048(); // 构造函数
    int getScore() const; // 获取分数函数
    void updateScore(int value); // 更新分数函数
private:
    int score;
    std::list<Tile> tiles;
};

#endif // GAME2048_H

#include "game2048.h"

Game2048::Game2048() :
    score(0)
{

}

int Game2048::getScore() const
{
    return score;
}

void Game2048::updateScore(int value)
{
    score += value;
}

#ifndef RANKINGLIST_H
#define RANKINGLIST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>


class RankingList
{
public:
    RankingList();
    std::vector<int> recordScore(int score);
};

#endif // RANKINGLIST_H

#include "rankinglist.h"

RankingList::RankingList()
{

}

int RankingList::recordScore(int score)
{
    bool cmp(int x, int y);
    std::string line;
    std::vector<int> sco;
    std::size_t i = 0;
    int x;
    std::ifstream infile("RankingList.txt");
    while(getline(infile, line))
    {
        std::istringstream items(line);
        items >> x;
        sco[i] = x;
        i++;
    }
    sco[i] = score;
    sort(sco.begin(), sco.end());
    std::ofstream outfile("RankingList.txt");
    for (std::size_t i = 0; i < sco.size(); i++)
    {
        outfile << sco[i] << '\t';
    }
    infile.close();
    outfile.close();
    return sco[0];
}

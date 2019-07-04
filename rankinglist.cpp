#include "rankinglist.h"

RankingList::RankingList()
{

}

int RankingList::recordScore(int scoreThis)
{
    std::string line;
    std::vector<int> score;
    std::size_t i = 0;
    int x;
    std::ifstream infile("RankingList.txt");
    while(getline(infile, line))
    {
        std::istringstream items(line);
        while (items >> x)
        {
            score[i] = x;
            i++;
        }
    }
    score[i] = scoreThis;
    sort(score.begin(), score.end());
    reverse(score.begin(), score.end());
    std::ofstream outfile("RankingList.txt");
    for (std::size_t j = 0; j < score.size(); j++)
    {
        outfile << score[j] << '\t';
    }
    infile.close();
    outfile.close();
    return score[0];
}

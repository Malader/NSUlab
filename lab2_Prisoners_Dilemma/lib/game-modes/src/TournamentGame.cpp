#include "TournamentGame.h"

#include <algorithm>
#include <iostream>

TournamentGame::TournamentGame(std::vector<std::string> strategiesNames, const int &moves) : strategiesNames_(std::move(
        strategiesNames)), moves_(moves)
{}

void TournamentGame::run()
{
    std::vector<std::pair<int, int>> roundResults;

    std::vector<int> winners;

    int maxRoundResult = 0;

    for (auto itFirst = strategiesNames_.begin(); itFirst != std::prev(strategiesNames_.end(), 2); ++itFirst)
    {
        for (auto itSecond = std::next(itFirst); itSecond != std::prev(strategiesNames_.end()); ++itSecond)
        {
            for (auto itThird = std::next(itSecond); itThird != strategiesNames_.end(); ++itThird)
            {
                std::cout << "\t\tPlayers " <<
                          itFirst - strategiesNames_.begin() + 1 << " " <<
                          itSecond - strategiesNames_.begin() + 1 << " " <<
                          itThird - strategiesNames_.begin() + 1 <<
                          " are playing now!\n" << std::endl;

                std::vector<std::string> playersNames;

                playersNames.push_back(*itFirst);
                playersNames.push_back(*itSecond);
                playersNames.push_back(*itThird);

                FastGame game = FastGame(playersNames, moves_);
                game.run();

                roundResults = game.getWinners();

                for (auto player: roundResults)
                {
                    if (player.second >= maxRoundResult)
                    {

                        int playerNum;

                        switch (player.first)
                        {
                            case 0:
                                playerNum = itFirst - strategiesNames_.begin() + 1;
                                break;
                            case 1:
                                playerNum = itSecond - strategiesNames_.begin() + 1;
                                break;
                            case 2:
                                playerNum = itThird - strategiesNames_.begin() + 1;
                                break;
                        }

                        if (player.second != maxRoundResult)
                        {
                            maxRoundResult = player.second;

                            winners.clear();
                            winners.push_back(playerNum);

                            continue;
                        }

                        if (std::find(winners.begin(), winners.end(), playerNum) == winners.end())
                        {
                            winners.push_back(playerNum);
                        }
                    }
                }

            }
        }
    }

    if (winners.size() == 1)
    {
        std::cout << "\n\t\tWinner of Tournament: ";
    }
    else
    {
        std::cout << "\n\t\tWinners of Tournament: ";
    }

    for (int i = 0; i < winners.size(); ++i)
    {
        if (i == 0)
        {
            std::cout << winners[i];
            continue;
        }

        std::cout << ", " << winners[i];
    }

    std::cout << " with score " << maxRoundResult << "!" << std::endl;
}
#include "FastGame.h"

FastGame::FastGame(std::vector<std::string> strategiesNames, const int &moves) : game_(Game(std::move(strategiesNames))), moves_(moves) {}

void FastGame::run()
{
    for (int i = 0; i < moves_; i++)
    {
        game_.makeMove();
    }

    game_.printGameStatus();
    game_.finishGame();
}

std::vector<std::pair<int, int>> FastGame::getWinners() const
{
    return game_.getWinners();
}

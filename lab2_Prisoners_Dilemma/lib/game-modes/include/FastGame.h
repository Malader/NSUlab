#pragma once

#include "Game.h"
#include "IGameMode.h"

class FastGame : public IGameMode
{
private:
    Game game_;

    int moves_;


public:
    FastGame(std::vector<std::string> strategiesNames, const int &moves);

    ~FastGame() override = default;

    void run() override;

    std::vector<std::pair<int, int>> getWinners() const;
};

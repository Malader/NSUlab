#pragma once

#include "FastGame.h"

class TournamentGame : public IGameMode
{
private:
    std::vector<std::string> strategiesNames_; 

    int moves_;

public:
    TournamentGame(std::vector<std::string> strategiesNames, const int &moves);
    
    ~TournamentGame() override = default;

    void run() override;
};

#pragma once

#include <vector>
#include <string>
#include <memory>

#include "IStrategy.h"
#include "PlayingField.h"

class Game
{
private:
    std::vector<std::shared_ptr<IStrategy>> players_;

    PlayingField playingField_;

    int currentMove_ = 1;

public:
    Game() = default;

    Game(std::vector<std::string> strategiesNames);

    ~Game() = default;

    void makeMove();

    void printGameStatus() const;

    void finishGame();

    std::vector<std::pair<int, int>> getWinners() const;
};


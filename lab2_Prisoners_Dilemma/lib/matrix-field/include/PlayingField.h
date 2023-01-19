#pragma once

#include "MoveMatrix.h"
#include "ResultMatrix.h"
#include "StrategyFactory.h"

class PlayingField
{
private:
    ResultMatrix resultMatrix_;
    MoveMatrix moveMatrix_;

    std::vector<std::pair<int, int>> winners_;

public:
    PlayingField() = default;

    ~PlayingField() = default;

    std::string getLine(int height);

    std::pair<PlayerChoice, PlayerChoice> getOpponentsMoves(int playerNumber, int height);

    void makeMoves(std::vector<std::shared_ptr<IStrategy>> players, int &currentMove);

    void countMoveResult(const std::string &moves, const int &currentMove);

    std::vector<std::pair<int, int>> getWinners() const;

    void printGameStatus(const int &currentMove) const;

    void printGameResult();
};
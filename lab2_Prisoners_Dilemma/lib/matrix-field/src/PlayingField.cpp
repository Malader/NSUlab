#include "PlayingField.h"

#include <iostream>

namespace
{
    int findIdMax(std::vector<int> v)
    {
        int idMax = 0;

        for (int i = 0; i < v.size() - 1; ++i)
        {
            if (v[idMax] < v[i + 1])
            {
                idMax = i + 1;
            }
        }

        return idMax;
    }
}

std::string PlayingField::getLine(int height)
{
    return moveMatrix_.getLine(height);
}

std::pair<PlayerChoice, PlayerChoice> PlayingField::getOpponentsMoves(int playerNumber, int height)
{
    std::string line = moveMatrix_.getLine(height);

    std::pair<PlayerChoice, PlayerChoice> opponentsMoves;

    bool isFirstAtPair = true;

    int playerIter = 0;

    for (const auto &item: line)
    {
        if (item == ' ')
        {
            continue;
        }

        if (playerIter == playerNumber)
        {
            ++playerIter;
            continue;
        }

        if (isFirstAtPair)
        {
            opponentsMoves.first = (item == 'D' ? PlayerChoice::evBetray : PlayerChoice::evCooperate);
            isFirstAtPair = false;
        }
        else
        {
            opponentsMoves.second = (item == 'D' ? PlayerChoice::evBetray : PlayerChoice::evCooperate);
        }
    }

    return opponentsMoves;
}

std::vector<std::pair<int, int>> PlayingField::getWinners() const
{
    return winners_;
}

void PlayingField::makeMoves(std::vector<std::shared_ptr<IStrategy>> players,
                             int &currentMove)
{
    for (int i = 0; i < players.size(); ++i)
    {
        moveMatrix_.addMove(i, players[i]->makeMove(), currentMove);
    }
}

void PlayingField::countMoveResult(const std::string &moves, const int &currentMove)
{
    resultMatrix_.countMoveResult(moves, currentMove);
}

void PlayingField::printGameStatus(int const &currentMove) const
{
    for (int i = 0; i < currentMove + 1; ++i)
    {
        std::cout << "\t\t" << moveMatrix_.getLine(i);
        if (i == 0)
        {
            std::cout << "  =>   ";
        }
        else
        {
            std::cout << " =>   ";
        }

        std::cout << resultMatrix_.getLine(i) << std::endl;
    }
}

void PlayingField::printGameResult()
{
    std::cout << "\t\t\tGame result:" << std::endl;
    std::cout << "\t\t" << resultMatrix_.getLine(0) << std::endl;

    std::vector<int> result = resultMatrix_.countGameResult();
    std::cout << "\t\t ";

    for (int el: result)
    {
        std::cout << el << "  ";
    }

    std::cout << std::endl;

    int id = findIdMax(result);

    std::cout << "\n\t\t   The Winners: ";
    for (int i = 0; i < result.size(); ++i)
    {
        if (result[i] == result[id])
        {
            if (i == id)
            {
                winners_.emplace_back(i, result[i]);
                std::cout << i + 1;
            }
            else
            {
                std::cout << ", " << i + 1;
            }
        }
    }
    std::cout << " with score " << result[id] << "!\n"
              << std::endl;
}
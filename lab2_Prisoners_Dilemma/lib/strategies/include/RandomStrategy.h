#pragma once

#include "IStrategy.h"
#include "PlayerChoice.h"

class RandomStrategy : public IStrategy
{
public:
    RandomStrategy() = default;

    ~RandomStrategy() override = default;

    void opponentsMoves(PlayerChoice opponent1Move, PlayerChoice opponent2Move) override;

    PlayerChoice makeMove() override;
};
#pragma once

#include "IStrategy.h"

class AlwaysBetrayerStrategy : public IStrategy
{
public:
    AlwaysBetrayerStrategy() = default;

    ~AlwaysBetrayerStrategy() override = default;

    void opponentsMoves(PlayerChoice opponent1Move, PlayerChoice opponent2Move) override;

    PlayerChoice makeMove() override;
};
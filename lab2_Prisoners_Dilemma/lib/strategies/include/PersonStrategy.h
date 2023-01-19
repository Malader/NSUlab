#pragma once

#include "IStrategy.h"

class PersonStrategy : public IStrategy
{
public:
    PersonStrategy() = default;

    ~PersonStrategy() override = default;

    void opponentsMoves(PlayerChoice opponent1Move, PlayerChoice opponent2Move) override;

    PlayerChoice makeMove() override;
};
#pragma once

#include "PlayerChoice.h"

class IStrategy
{
public:
    virtual ~IStrategy() = default;

    virtual void opponentsMoves(PlayerChoice opponent1Move, PlayerChoice opponent2Move) = 0;

    virtual PlayerChoice makeMove() = 0;
};
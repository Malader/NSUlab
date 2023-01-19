#pragma once

#include "IStrategy.h"
#include "PlayerChoice.h"

class SmartStrategy : public IStrategy
{
private:
    PlayerChoice opponent1Move_ = PlayerChoice::evCooperate;

    PlayerChoice opponent2Move_ = PlayerChoice::evCooperate;

public:
    SmartStrategy() = default;

    ~SmartStrategy() override = default;

    void opponentsMoves(PlayerChoice opponent1Move, PlayerChoice opponent2Move) override;

    PlayerChoice makeMove() override;
};
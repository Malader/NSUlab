#pragma once

#include "IStrategy.h"
#include "ResultMatrix.h"
#include "PlayerChoice.h"

class AlternatingStrategy : public IStrategy
{
private:
    ResultMatrix resultMatrix_;

    bool isBetrayer_ = false;

public:
    AlternatingStrategy() = default;

    ~AlternatingStrategy() override = default;

    void opponentsMoves(PlayerChoice opponent1Move, PlayerChoice opponent2Move) override;

    PlayerChoice makeMove() override;
};

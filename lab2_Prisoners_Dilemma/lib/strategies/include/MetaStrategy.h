#pragma once

#include <memory>

#include "IStrategy.h"

class MetaStrategy : public IStrategy
{
private:
    int betrayerCounter_ = 0;
    int cooperatorCounter_ = 0;

    std::shared_ptr<IStrategy> strategy_;

    void updateStrategy();

public:
    MetaStrategy() = default;

    ~MetaStrategy() override = default;

    void opponentsMoves(PlayerChoice opponent1Move, PlayerChoice opponent2Move) override;

    PlayerChoice makeMove() override;
};
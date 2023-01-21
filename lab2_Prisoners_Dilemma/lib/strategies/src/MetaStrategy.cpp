#include "MetaStrategy.h"

#include <string>

#include "StrategyFactory.h"

void MetaStrategy::updateStrategy()
{
    auto factory = &StrategyFactory::getInstance();

    if (cooperatorCounter_ > betrayerCounter_)
    {
        strategy_ = factory->create("smart");
        return;
    }

    if (cooperatorCounter_ == betrayerCounter_)
    {
        strategy_ = factory->create("random");
        return;
    }

    strategy_ = factory->create("betrayer");
}

void MetaStrategy::opponentsMoves(PlayerChoice opponent1Move, PlayerChoice opponent2Move)
{
    opponent1Move == PlayerChoice::evCooperate ? ++cooperatorCounter_ : ++betrayerCounter_;
    opponent2Move == PlayerChoice::evCooperate ? ++cooperatorCounter_ : ++betrayerCounter_;
}

PlayerChoice MetaStrategy::makeMove()
{
    updateStrategy();
    return strategy_->makeMove();
}
#include "SmartStrategy.h"

void SmartStrategy::opponentsMoves(PlayerChoice opponent1Move, PlayerChoice opponent2Move)
{
    opponent1Move_ = opponent1Move;
    opponent2Move_ = opponent2Move;
}

PlayerChoice SmartStrategy::makeMove()
{
    if (opponent2Move_ == PlayerChoice::evCooperate && opponent1Move_ == PlayerChoice::evCooperate)
    {
        return PlayerChoice::evCooperate;
    }

    return PlayerChoice::evBetray;
}
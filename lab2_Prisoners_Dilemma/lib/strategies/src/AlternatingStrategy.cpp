#include "AlternatingStrategy.h"

PlayerChoice AlternatingStrategy::makeMove()
{
    isBetrayer_ = !isBetrayer_;
    return !isBetrayer_ ? PlayerChoice::evCooperate : PlayerChoice::evBetray;
}

void AlternatingStrategy::opponentsMoves(PlayerChoice opponent1Move, PlayerChoice opponent2Move)
{}
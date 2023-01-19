#include "AlwaysBetrayerStrategy.h"

void AlwaysBetrayerStrategy::opponentsMoves(PlayerChoice opponent1Move, PlayerChoice opponent2Move)
{}

PlayerChoice AlwaysBetrayerStrategy::makeMove()
{
    return PlayerChoice::evBetray;
}
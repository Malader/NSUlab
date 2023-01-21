#include "RandomStrategy.h"

#include <random>

void RandomStrategy::opponentsMoves(PlayerChoice opponent1Move, PlayerChoice opponent2Move)
{}

PlayerChoice RandomStrategy::makeMove()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 2);

    return distrib(gen) % 2 == 0 ? PlayerChoice::evCooperate : PlayerChoice::evBetray;
}
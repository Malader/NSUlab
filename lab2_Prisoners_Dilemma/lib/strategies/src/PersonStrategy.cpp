#include "PersonStrategy.h"

#include <iostream>

void PersonStrategy::opponentsMoves(PlayerChoice opponent1Move, PlayerChoice opponent2Move)
{
}

PlayerChoice PersonStrategy::makeMove()
{
    std::cout << "\t\t\tMake move:" << std::endl
              << "\t\t\t'C' - to cooperate" << std::endl
              << "\t\t\t'D' - to betray" << std::endl;

    std::string move;
    
    while (true)
    {
        std::getline(std::cin, move);

        if (move == "D")
        {
            return PlayerChoice::evBetray;
        }
        if (move == "C")
        {
            return PlayerChoice::evCooperate;
        }

        std::cout << std::endl
                  << "You entered wrong move, try again" << std::endl;
    }
}
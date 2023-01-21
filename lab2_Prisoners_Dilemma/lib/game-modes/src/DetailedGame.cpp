#include "DetailedGame.h"

#include <iostream>

DetailedGame::DetailedGame(std::vector<std::string> strategiesNames) :
        game_(Game(std::move(strategiesNames)))
{}

void DetailedGame::initialize()
{
    userInputValuesMap_["start"] = UserInputValues::evStart;
    userInputValuesMap_[""] = UserInputValues::evContinue;
    userInputValuesMap_["quit"] = UserInputValues::evQuit;
}

void DetailedGame::run()
{
    initialize();

    bool isStarted = false;
    bool isFinished = false;

    std::string inputMessage;

    while (!isFinished)
    {
        std::getline(std::cin, inputMessage);

        switch (userInputValuesMap_[inputMessage])
        {
            case UserInputValues::evStart:
                if (isStarted)
                {
                    std::cout << "\t\t\tGame already started" << std::endl;
                    continue;
                }
                isStarted = true;

            case UserInputValues::evContinue:
                game_.makeMove();
                game_.printGameStatus();
                break;

            case UserInputValues::evQuit:
                if(!isStarted)
                {
                    return;
                }

                isFinished = true;
                break;

            default:
                std::cout << "\t\t\tYou entered the wrong message. Try again." << std::endl;
                continue;
        }
    }
    game_.finishGame();
}
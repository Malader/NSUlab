#include "GameHub.h"

#include <iostream>
#include <ctime>

#include "FastGame.h"
#include "DetailedGame.h"
#include "TournamentGame.h"

#include "AlwaysBetrayerStrategy.h"
#include "AlternatingStrategy.h"
#include "SmartStrategy.h"
#include "PersonStrategy.h"
#include "RandomStrategy.h"
#include "MetaStrategy.h"

namespace
{
    void printCommandMessage()
    {
        std::cout << "\n\t\t\tGame \"Prisoner's Dilemma\"\n\n "
                  << "\tTo start the game write \'start\'\n"
                  << "\tTo end the game write \'quit\'\n"
                  << std::endl;
    }
}

void GameHub::ParsingCommandLineArgs::initialize(GameHub &game)
{
    commandsValuesMap_["--steps"] = CommandsValues::evSteps;
    commandsValuesMap_["--mode"] = CommandsValues::evMode;
    commandsValuesMap_["--matrix"] = CommandsValues::evMatrix;

    StrategyFactory *factory = &StrategyFactory::getInstance();

    factory->registerCreator("betrayer", std::make_shared<Creator<AlwaysBetrayerStrategy>>());
    factory->registerCreator("alternating", std::make_shared<Creator<AlternatingStrategy>>());
    factory->registerCreator("random", std::make_shared<Creator<RandomStrategy>>());
    factory->registerCreator("smart", std::make_shared<Creator<SmartStrategy>>());
    factory->registerCreator("person", std::make_shared<Creator<PersonStrategy>>());
    factory->registerCreator("meta",std::make_shared<Creator<MetaStrategy>>());
}

bool GameHub::ParsingCommandLineArgs::parseCommand(GameHub &game, std::string &str)
{
    auto fPos = str.find('=');

    if (fPos == -1 || fPos == str.size() - 1)
    {
        std::cerr << "\t\t\tParameter entered incorrectly";
        return true;
    }

    std::string_view argView = str;

    switch (commandsValuesMap_[argView.substr(0, fPos)])
    {
    case CommandsValues::evMode:

        if (!game.gameModeName_.empty())
        {
            std::cerr << "\t\t\tYou have already chosen game mode" << std::endl;
            return true;
        }

        game.gameModeName_ = argView.substr(fPos + 1);

        break;

    case CommandsValues::evSteps:
        try
        {
            game.numOfMoves_ = std::stoi(str.substr(fPos + 1));
            game.isNumOfMovesChanged_ = true;

            if (game.numOfMoves_ <= 0)
            {
                throw std::exception();
            }
        }
        catch (std::exception &ex)
        {
            std::cerr << "\t\t\t"
                      << "You entered wrong --steps param" << std::endl;
            return true;
        }

        break;

    default:
        std::cerr << "\t\t\tParameter entered incorrectly" << std::endl;
        return true;
    }
    return false;
}

bool GameHub::ParsingCommandLineArgs::chooseGameMode(GameHub &game, const std::vector<std::string> &strategiesNames) {
    if (game.gameModeName_.empty())
    {
        if (strategiesNames.size() > 3)
        {
            game.gameMode_ = std::make_unique<TournamentGame>(strategiesNames, game.numOfMoves_);
        }
        else
        {
            if(game.isNumOfMovesChanged_)
            {
                std::cerr << "Detailed game mode do not support --steps option";
                return true;
            }

            game.gameMode_ = std::make_unique<DetailedGame>(strategiesNames);
        }
        return false;
    }

    if (game.gameModeName_ == "tournament")
    {
        if (strategiesNames.size() == 3)
        {
            std::cerr << "Few players for tournament mode" << std::endl;
            return true;
        }
        game.gameMode_ = std::make_unique<TournamentGame>(strategiesNames, game.numOfMoves_);

        return false;
    }

    if (strategiesNames.size() > 3)
    {
        std::cerr << "Too much players for this game mode" << std::endl;
        return true;
    }

    if (game.gameModeName_ == "detailed")
    {
        if(game.isNumOfMovesChanged_)
        {
            std::cerr << "Detailed game mode do not support --steps option";
            return true;
        }

        game.gameMode_ = std::make_unique<DetailedGame>(strategiesNames);
        return false;
    }
    if (game.gameModeName_ == "fast")
    {
        game.gameMode_ = std::make_unique<FastGame>(strategiesNames, game.numOfMoves_);
        return false;
    }

    std::cerr << "Name of game mode entered incorrectly" << std::endl;
    return true;
}


bool GameHub::ParsingCommandLineArgs::parseLine(GameHub &game)
{
    initialize(game);

    std::vector<std::string> strategiesNames;

    StrategyFactory *factory = &StrategyFactory::getInstance();

    for (int i = 1; i < game.argv_.size(); ++i)
    {
        if (game.argv_[i][0] == '-' && game.argv_[i][1] == '-')
        {
            if (parseCommand(game, game.argv_[i]))
            {
                std::cerr << "\t\t\tParameter entered incorrectly" << std::endl;
                return true;
            }
            continue;
        }

        if (!factory->canCreateStrategy(game.argv_[i]))
        {
            std::cerr << "\t\t\t" << game.argv_[i] << " : no such strategy exists" << std::endl;
            return true;
        }

        strategiesNames.push_back(game.argv_[i]);
    }

    while (strategiesNames.size() < 3)
    {
        strategiesNames.push_back("alternating");
    }

    return chooseGameMode(game,strategiesNames);
}

GameHub::GameHub(int argc, const char **argv)
{
    for (int i = 0; i < argc; ++i)
    {
        this->argv_.emplace_back(argv[i]);
    }
}

void GameHub::run()
{
    if (parsing_->parseLine(*this))
    {
        return;
    }

    printCommandMessage();

    gameMode_->run();
}
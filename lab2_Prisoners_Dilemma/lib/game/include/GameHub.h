#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "IGameMode.h"

class GameHub
{
private:
    class ParsingCommandLineArgs
    {
        enum class CommandsValues
        {
            evMode,
            evSteps,
            evMatrix
        };

        std::map<std::string_view, CommandsValues> commandsValuesMap_;

        void initialize(GameHub &);

        bool parseCommand(GameHub &game, std::string &str);

        bool chooseGameMode(GameHub& game, const std::vector<std::string> &strategiesNames);
    public:
        ParsingCommandLineArgs() = default;

        bool parseLine(GameHub &);
    };

    std::vector<std::string> argv_;

    std::unique_ptr<ParsingCommandLineArgs> parsing_ = std::make_unique<ParsingCommandLineArgs>();

    std::string_view gameModeName_;
    std::unique_ptr<IGameMode> gameMode_ = nullptr;

    bool isNumOfMovesChanged_ = false;

    int numOfMoves_ = 5;

public:
    GameHub(int argc, const char **argv);

    ~GameHub() = default;

    void run();
};

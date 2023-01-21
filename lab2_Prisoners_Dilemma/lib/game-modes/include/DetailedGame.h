#pragma once

#include "Game.h"
#include "IGameMode.h"

class DetailedGame : public IGameMode
{
private:
    enum class UserInputValues
    {
        evStart,
        evContinue,
        evQuit
    };

    std::map<std::string, UserInputValues> userInputValuesMap_;

    Game game_;

    void initialize();

public:
    DetailedGame(std::vector<std::string> strategiesNames);

    ~DetailedGame() override = default;

    void run() override;
};
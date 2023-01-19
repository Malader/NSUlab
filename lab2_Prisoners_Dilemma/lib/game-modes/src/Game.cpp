#include "Game.h"

#include "StrategyFactory.h"

Game::Game(std::vector<std::string> strategiesNames)
{
    StrategyFactory *factory = &StrategyFactory::getInstance();

    for (int i = 0; i < 3; i++)
    {
        std::shared_ptr<IStrategy> player = factory->create(strategiesNames[i]);

        players_.push_back(player);
    }
}

void Game::makeMove()
{
    playingField_.makeMoves(players_, currentMove_);

    for (int i = 0; i < players_.size(); ++i)
    {
        std::pair<PlayerChoice, PlayerChoice> opponentMoves = playingField_.getOpponentsMoves(i, currentMove_);
        players_[i]->opponentsMoves(opponentMoves.first, opponentMoves.second);
    }

    playingField_.countMoveResult(playingField_.getLine(currentMove_), currentMove_);
    ++currentMove_;
}

void Game::printGameStatus() const
{
    playingField_.printGameStatus(currentMove_ - 1);
}

void Game::finishGame()
{
    playingField_.printGameResult();
}

std::vector<std::pair<int, int>> Game::getWinners() const
{
    return playingField_.getWinners();
}

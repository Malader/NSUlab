#include "StrategyFactory.h"

#include <string>

StrategyFactory &StrategyFactory::getInstance()
{
    static StrategyFactory instance;
    return instance;
}

void StrategyFactory::registerCreator(std::string strategyName, std::shared_ptr<ICreator> creator)
{
    factoryMap_.insert({std::move(strategyName), std::move(creator)});
}

std::shared_ptr<IStrategy> StrategyFactory::create(const std::string &strategyName)
{
    auto it = factoryMap_.find(strategyName);
    if (it == factoryMap_.end())
    {
        return nullptr;
    }

    return it->second->create();
}

bool StrategyFactory::canCreateStrategy(const std::string &strategyName)
{
    return factoryMap_.find(strategyName) != factoryMap_.end();
}
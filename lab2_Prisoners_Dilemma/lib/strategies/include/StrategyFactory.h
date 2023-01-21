#pragma once

#include <map>
#include <memory>

#include "IStrategy.h"

class ICreator
{
public:
    virtual ~ICreator() = default;

    virtual std::shared_ptr<IStrategy> create() = 0;
};

template <typename T>
class Creator : public ICreator
{
public:
    std::shared_ptr<IStrategy> create() override
    {
        return std::make_shared<T>();
    }
};

class StrategyFactory
{
private:
    std::map<std::string, std::shared_ptr<ICreator>> factoryMap_;

    StrategyFactory() = default;

public:
    StrategyFactory(const StrategyFactory &) = delete;

    StrategyFactory(StrategyFactory &&) = delete;

    static StrategyFactory &getInstance();

    void registerCreator(std::string strategy_name, std::shared_ptr<ICreator> creator);

    std::shared_ptr<IStrategy> create(const std::string &strategy_name);

    bool canCreateStrategy(const std::string &strategyName);
};
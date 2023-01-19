#pragma once 

class IGameMode
{
public:
    virtual ~IGameMode() = default;

    virtual void run() = 0;
};

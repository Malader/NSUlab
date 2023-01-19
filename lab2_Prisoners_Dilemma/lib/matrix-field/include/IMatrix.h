#pragma once

#include <string>

class IMatrix
{
public:
    virtual ~IMatrix() {}
    virtual std::string getLine(const int &) const = 0;
};
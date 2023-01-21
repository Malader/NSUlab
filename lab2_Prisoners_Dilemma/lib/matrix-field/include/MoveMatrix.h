#pragma once

#include <vector>

#include "IMatrix.h"
#include "PlayerChoice.h"

class MoveMatrix : private IMatrix
{
private:
    std::vector<std::vector<std::string>> matrix_;

    static constexpr int weight_ = 3;

    int matrixSize_ = 1;

public:
    MoveMatrix();

    ~MoveMatrix() override = default;

    std::string getLine(const int &height) const override;

    void addMove(const int &numOfPlayer, const PlayerChoice &moveChoice, const int &currentMove);
};
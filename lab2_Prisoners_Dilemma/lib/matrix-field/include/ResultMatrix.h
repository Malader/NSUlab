#pragma once

#include <vector>

#include "IMatrix.h"

class ResultMatrix : private IMatrix
{
    std::vector<std::vector<std::string>> matrix_;

    static constexpr int weight_ = 3;

    int matrixSize_ = 1;

public:
    ResultMatrix();

    ~ResultMatrix() override = default;

    std::string getLine(const int &height) const override;

    void countMoveResult(const std::string &moves, const int &currentMove);

    std::vector<int> countGameResult() const;
};
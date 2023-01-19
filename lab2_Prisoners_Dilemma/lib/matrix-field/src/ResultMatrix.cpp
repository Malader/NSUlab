#include "ResultMatrix.h"

ResultMatrix::ResultMatrix()
{
    matrix_.resize(1);
    matrix_[0].resize(weight_);

    for (int i = 0; i < weight_; ++i)
    {
        matrix_[0][i] = "Pr" + std::to_string(i + 1);
    }
}

std::string ResultMatrix::getLine(const int &height) const
{
    std::string str;
    if (height != 0)
        str += " ";

    for (int i = 0; i < weight_; ++i)
    {
        str += matrix_[height][i];
        height == 0 ? str += " " : str += "   ";
    }

    return str;
}

void ResultMatrix::countMoveResult(const std::string &moves, const int &currentMove)
{
    if (currentMove == matrixSize_)
    {
        matrix_.emplace_back(3);
        ++matrixSize_;
    }

    int traitors = 0;
    int employers = 0;

    int trPoints = 0;
    int emPoints = 0;

    for (char move: moves)
    {
        if (move == ' ')
        {
            continue;
        }

        move == 'D' ? ++traitors : ++employers;
    }

    if (employers == 0)
    {
        trPoints = 1;
    }
    else if (traitors == 0)
    {
        emPoints = 7;
    }
    else if (employers == 1)
    {
        trPoints = 5;
    }
    else
    {
        trPoints = 9;
        emPoints = 3;
    }

    for (int i = 0, j = 0; i < weight_; ++j)
    {
        if (moves[j] == ' ')
        {
            continue;
        }
        moves[j] == 'C' ? matrix_[currentMove][i] = std::to_string(emPoints) : matrix_[currentMove][i] = std::to_string(
                trPoints);
        ++i;
    }
}

std::vector<int> ResultMatrix::countGameResult() const
{
    std::vector<int> result;
    for (int i = 0; i < weight_; ++i)
    {
        result.push_back(0);
        for (int j = 1; j < matrixSize_; ++j)
        {
            result[i] += std::atoi(matrix_[j][i].c_str());
        }
    }

    return result;
}
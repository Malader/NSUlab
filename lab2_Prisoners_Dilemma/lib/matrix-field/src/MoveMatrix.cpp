#include "MoveMatrix.h"

MoveMatrix::MoveMatrix()
{
    matrix_.resize(1);
    matrix_[0].resize(weight_);

    for (int i = 0; i < weight_; ++i)
    {
        matrix_[0][i] = "Pr" + std::to_string(i + 1);
    }
}

std::string MoveMatrix::getLine(const int &height) const
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

void MoveMatrix::addMove(const int &numOfPlayer, const PlayerChoice &moveChoice, const int &currentMove)
{
    if (currentMove == matrixSize_)
    {
        matrix_.emplace_back(3);
        ++matrixSize_;
    }
    moveChoice == PlayerChoice::evBetray ? matrix_[currentMove][numOfPlayer] = "D"
                                         : matrix_[currentMove][numOfPlayer] = "C";
}
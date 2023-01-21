#include "MuteConverter.hpp"
#include "ConverterException.hpp"

MuteConverter::MuteConverter(ConverterParams params)
{
    if (params.firstParam_ < 0)
    {
        throw ConverterExceptions::BadFirstArgumentMuteConverter(params.firstParam_);
    }
    if (params.secondParam_ < 0 || params.secondParam_ <= params.firstParam_)
    {
        throw  ConverterExceptions::BadSecondArgumentMuteConverter(params.secondParam_);
    }

    secStart_ = params.firstParam_;
    secEnd_ = params.secondParam_;
}

void MuteConverter::convert(SampleBuffer &outputSample, SampleVector const &)
{
    if (currentSec_ >= secStart_ && currentSec_ <= secEnd_)
    {
        outputSample.fill(0);
    }
    ++currentSec_;
}
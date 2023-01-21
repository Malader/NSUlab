#include "MixConverter.hpp"
#include "ConverterException.hpp"

#include <algorithm>

MixConverter::MixConverter(ConverterParams params)
{
    if (params.firstParam_ < 1)
    {
        // throw exception about invalid id for mix
        throw  ConverterExceptions::BadFirstArgumentMixConverter(params.firstParam_);
    }
    if (params.secondParam_ < 0)
    {
        // throw exception about invalid second start
        throw  ConverterExceptions::BadSecondArgumentMixConverter(params.secondParam_);
    }

    idWAVForMix_ = params.firstParam_;
    secStart_ = params.secondParam_;
}

void MixConverter::convert(SampleBuffer &outputSample, SampleVector const &inputSamples)
{
    if (currentSec_ >= secStart_)
    {
        for (int i = 0; i < outputSample.size(); ++i)
        {
            outputSample[i] = outputSample[i] / 2 + inputSamples[idWAVForMix_ - 1][i] / 2;
        }
    }
    ++currentSec_;
}
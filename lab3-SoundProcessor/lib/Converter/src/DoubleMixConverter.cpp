#include "DoubleMixConverter.hpp"

#include "ConverterException.hpp"

DoubleMixConverter::DoubleMixConverter(ConverterParams params)
{
    if (params.firstParam_ < 1)
    {
        throw ConverterExceptions::BadFirstArgumentDoubleMixConverter(params.firstParam_);
    }
    if (params.secondParam_ < 1)
    {
        throw ConverterExceptions::BadSecondArgumentDoubleMixConverter(params.secondParam_);
    }
    if (params.secondParam_ == params.firstParam_)
    {
        throw ConverterExceptions::RecurringSecondArgumentDoubleMixConverter(params.secondParam_);
    }

    idFirstWAVForMix_ = params.firstParam_;
    idSecondWAVFormMix_ = params.secondParam_;
}

void DoubleMixConverter::convert(SampleBuffer &outputSample, SampleVector const &inputSamples)
{
    if (idFirstWAVForMix_ >= inputSamples.size())
    {
        throw ConverterExceptions::BadFirstArgumentDoubleMixConverter(idFirstWAVForMix_);
    }
    if (idSecondWAVFormMix_ >= inputSamples.size())
    {
        throw ConverterExceptions::BadSecondArgumentDoubleMixConverter(idSecondWAVFormMix_);
    }

    for (int i = 0; i < outputSample.size(); ++i)
    {
        outputSample[i] =
                outputSample[i] / 3
                + inputSamples[idFirstWAVForMix_ - 1][i] / 3
                + inputSamples[idSecondWAVFormMix_ - 1][i] / 3;
    }
}
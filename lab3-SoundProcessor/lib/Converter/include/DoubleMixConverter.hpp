#pragma once

#include "IConverter.hpp"

#include "WAVTypes.hpp"

class DoubleMixConverter : public IConverter
{
private:
    int idFirstWAVForMix_;

    int idSecondWAVFormMix_;

public:
    DoubleMixConverter(ConverterParams);

    void convert(SampleBuffer &outputSample, SampleVector const &inputSamples) override;
};


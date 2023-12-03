#pragma once

#include "IConverter.hpp"

#include "WAVTypes.hpp"

class MixConverter : public IConverter
{
private:
    int idWAVForMix_;

    int secStart_;

    int currentSec_ = 0;

public:
    MixConverter(ConverterParams);

    void convert(SampleBuffer &outputSample, SampleVector const &inputSamples) override;
};

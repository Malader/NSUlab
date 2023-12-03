#pragma once

#include "IConverter.hpp"


class MuteConverter : public IConverter
{
private:
    int secStart_;

    int secEnd_;

    int currentSec_ = 0;

public:
    MuteConverter(ConverterParams);

    void convert(SampleBuffer &outputSample, SampleVector const &) override;
};
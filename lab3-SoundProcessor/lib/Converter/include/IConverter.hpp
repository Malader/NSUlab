#pragma once

#include <fstream>
#include <memory>

#include "WAVTypes.hpp"

class IConverter;

using ConverterPtr = std::shared_ptr<IConverter>;

using ConverterPipeline = std::vector<ConverterPtr>;

struct ConverterParams
{
    int firstParam_;
    int secondParam_;
};

class IConverter
{
public:
    ~IConverter() = default;

    virtual void convert(SampleBuffer &outputSample, SampleVector const &inputSamples) = 0;
};


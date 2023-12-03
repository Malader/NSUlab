#include "ConverterCreator.hpp"

#include "MuteConverter.hpp"
#include "MixConverter.hpp"
#include "DoubleMixConverter.hpp"

ConverterPtr MuteConverterCreator::create(ConverterParams params) const
{
    return std::make_shared<MuteConverter>(params);
}

ConverterPtr MixConverterCreator::create(ConverterParams params) const
{
    return std::make_shared<MixConverter>(params);
}

ConverterPtr DoubleMixConverterCreator::create(ConverterParams params) const
{
    return std::make_shared<DoubleMixConverter>(params);
}
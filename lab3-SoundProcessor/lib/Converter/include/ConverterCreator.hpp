#pragma once

#include <memory>

#include "IConverter.hpp"

class ConverterCreator
{
public:
    virtual ~ConverterCreator() = default;

    virtual ConverterPtr create(ConverterParams params) const = 0;
};


class MuteConverterCreator : public ConverterCreator
{
public:
    ConverterPtr create(ConverterParams params) const override;
};

class MixConverterCreator : public ConverterCreator
{
public:
    ConverterPtr create(ConverterParams params) const override;
};

class DoubleMixConverterCreator : public ConverterCreator
{
public:
    ConverterPtr  create(ConverterParams params) const override;
};
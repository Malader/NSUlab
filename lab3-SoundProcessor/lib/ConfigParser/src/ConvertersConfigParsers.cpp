#include "ConvertersConfigParsers.hpp"

ConverterParams MuteConverterParser::parseConverterConfig(const std::vector<std::string_view> &&splitLine)
{
    ConverterParams params {};

    try
    {
        params.firstParam_ = std::stoi(std::string(splitLine[1]));
        params.secondParam_ = std::stoi(std::string(splitLine[2]));

        if(params.firstParam_ < 0 || params.secondParam_ < 0)
        {
            throw std::exception();
        }

        if(params.firstParam_ > params.secondParam_)
        {
            throw std::exception();
        }
    }
    catch (const std::exception &ex)
    {
        throw std::invalid_argument("bad config argument for mute converter");
    }

    return params;
}

MixConverterParser::MixConverterParser(int numInputFiles_) : numInputFiles_(numInputFiles_)
{}

ConverterParams MixConverterParser::parseConverterConfig(const std::vector<std::string_view> &&splitLine)
{
    ConverterParams params {};

    try
    {
        if (splitLine[1][0] != '$')
        {
            throw std::exception();
        }

        params.firstParam_ = std::stoi(std::string(splitLine[1].substr(1))) - 1;

        if(params.firstParam_ >= numInputFiles_)
        {
            throw std::exception();
        }

        params.secondParam_ = std::stoi(std::string(splitLine[2]));

        if(params.secondParam_ < 0)
        {
            throw std::exception();
        }
    }
    catch (const std::exception &ex)
    {
        throw std::invalid_argument("bad config arguments for mix converter");
    }

    return params;
}

DoubleMixConverterParser::DoubleMixConverterParser(int numInputFiles_) : numInputFiles_(numInputFiles_)
{}

ConverterParams DoubleMixConverterParser::parseConverterConfig(const std::vector<std::string_view> &&splitLine)
{
    ConverterParams params {};

    try
    {
        if(splitLine[1][0] != '$' || splitLine[2][0] != '$')
        {
            throw std::exception();
        }

        params.firstParam_ = std::stoi(std::string(splitLine[1].substr(1))) - 1;
        params.secondParam_ = std::stoi(std::string(splitLine[2].substr(1))) - 1;

        if(params.firstParam_ >= numInputFiles_ || params.secondParam_ >= numInputFiles_)
        {
            throw std::exception();
        }

    }
    catch (const std::exception &ex)
    {
        throw std::invalid_argument("bad config arguments for double mix converter");
    }

    return params;
}



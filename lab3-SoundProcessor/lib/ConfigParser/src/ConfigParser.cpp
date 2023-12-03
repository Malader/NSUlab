#include "ConfigParser.hpp"
#include "ConfigParserExceptions.hpp"
#include "ConvertersConfigParsers.hpp"

#include <iostream>
#include <vector>
/*
    # заглушить первые 30 секунд input1
    mute 0 30
    # смиксовать с input2, начиная с секунды 10
    mix $2 10
    # заглушить 3-ю минуту в миксованном потоке
    mute 120 180
    # применить ваш конвертер с нужными параметрами
    your_converter <parameters>
*/

namespace
{
    std::vector<std::string_view> splitString(std::string_view &&line)
    {
        std::string delimiter = " ";
        std::vector<std::string_view> splitStringVector;
        std::string::size_type pos = 0;

        while ((pos = line.find(delimiter)) != std::string::npos)
        {
            splitStringVector.push_back(line.substr(0, pos));
            line = line.substr(pos + 1);
        }
        if(!line.empty())
        {
            splitStringVector.push_back(line);
        }


        return splitStringVector;
    }
}


ConfigParser::ConfigParser(const std::string &configPath_, int numInputFiles_) : numInputFiles_(numInputFiles_)
{
    configFile_.open(configPath_, std::ios_base::binary);

    if (!configFile_.good())
    {
        // exception about не открыт конфиг файл
        throw ConfigExceptions::BadOpeningConfig(configPath_);
    }

    configFilePath_ = std::move(configPath_);

    readConfig();
}

void ConfigParser::readConfig()
{
    std::string line;
    std::string_view lineView;

    while (std::getline(configFile_, line, '\n'))
    {
        if (line.empty() || line[0] == ' ' || line[0] == '\t')
        {
            throw std::invalid_argument("unsupported config file format");
        }

        lineView = line;

        if (lineView[0] == '#')
        {
            continue;
        }

        std::vector<std::string_view> splitLineVector = splitString(std::move(lineView));

        if (splitLineVector.size() < 3)
        {
            throw std::invalid_argument("bad config line with arguments");
        }

        config_.push_back(ConfigParam());

        config_.back().converterName_ = splitLineVector[0];

        if (config_.back().converterName_ == "mute")
        {
            config_.back().converterParams_ =
                    MuteConverterParser().parseConverterConfig(std::move(splitLineVector));
        }
        else if (config_.back().converterName_ == "mix")
        {
            config_.back().converterParams_ =
                    MixConverterParser(numInputFiles_).parseConverterConfig(std::move(splitLineVector));
        }
        else if (config_.back().converterName_ == "dmix")
        {
            config_.back().converterParams_ =
                    DoubleMixConverterParser(numInputFiles_).parseConverterConfig(std::move(splitLineVector));
        }
        else
        {
            throw std::invalid_argument("bad config arguments :" + line);
        }
    }
}

ConfigParamLine ConfigParser::getConfig()
{
    return config_;
}
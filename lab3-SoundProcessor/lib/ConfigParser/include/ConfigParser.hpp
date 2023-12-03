#pragma once

#include "ConverterCreator.hpp"
#include <vector>

struct ConfigParam
{
    std::string converterName_;

    ConverterParams converterParams_;
};

using ConfigParamLine = std::vector<ConfigParam>;

class ConfigParser
{
private:
    std::ifstream configFile_;

    std::string configFilePath_;

    int numInputFiles_;

    ConfigParamLine config_;

    void readConfig();

public:
    ConfigParser(const std::string& configPath, int numInputFiles);

    ConfigParamLine getConfig();
};
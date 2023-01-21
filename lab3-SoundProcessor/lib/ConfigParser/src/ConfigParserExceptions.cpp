#include "ConfigParserExceptions.hpp"

using namespace ConfigExceptions;

BadOpeningConfig::BadOpeningConfig(const std::string &filePath) :
        std::invalid_argument("File didn't open :" + filePath)
{}
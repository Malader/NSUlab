#pragma once

#include <exception>
#include <string>
#include <stdexcept>

namespace ConfigExceptions
{
    class BadOpeningConfig : public std::invalid_argument
    {
    public:
        BadOpeningConfig(const std::string& filePath);
    };
}
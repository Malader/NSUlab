#pragma once

#include <exception>
#include <string>
#include <stdexcept>

namespace SoundProcessorExceptions
{
    class BadConverterName : public std::invalid_argument
    {
    public:
        explicit BadConverterName(const std::string &name);
    };

    class HelpArgument : public std::invalid_argument
    {
    public:
        HelpArgument();
    };
}
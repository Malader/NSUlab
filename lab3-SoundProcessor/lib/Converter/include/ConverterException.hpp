#pragma once

#include <string>
#include <stdexcept>

namespace ConverterExceptions
{
    class BadFirstArgumentMixConverter : public std::invalid_argument
    {
    public:
        explicit BadFirstArgumentMixConverter(int argument);
    };

    class BadSecondArgumentMixConverter : public std::invalid_argument
    {
    public:
        explicit BadSecondArgumentMixConverter(int argument);
    };

    class BadFirstArgumentMuteConverter : public std::invalid_argument
    {
    public:
        explicit BadFirstArgumentMuteConverter(int argument);
    };

    class BadSecondArgumentMuteConverter : public std::invalid_argument
    {
    public:
        explicit BadSecondArgumentMuteConverter(int argument);
    };

    class BadFirstArgumentDoubleMixConverter : public std::invalid_argument
    {
    public:
        explicit BadFirstArgumentDoubleMixConverter(int argument);
    };

    class BadSecondArgumentDoubleMixConverter : public std::invalid_argument
    {
    public:
        explicit BadSecondArgumentDoubleMixConverter(int argument);
    };

    class RecurringSecondArgumentDoubleMixConverter : public std::invalid_argument
    {
    public:
        explicit RecurringSecondArgumentDoubleMixConverter(int argument);
    };

}
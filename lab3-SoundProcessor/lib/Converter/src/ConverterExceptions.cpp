#include "ConverterException.hpp"

using namespace ConverterExceptions;

BadFirstArgumentMixConverter::BadFirstArgumentMixConverter(int argument) :
        std::invalid_argument("Bad first argument for mix converter :" + std::to_string(argument))
{}

BadSecondArgumentMixConverter::BadSecondArgumentMixConverter(int argument) :
std::invalid_argument("Bad second argument for mix converter : " + std::to_string(argument))
{}

BadFirstArgumentMuteConverter::BadFirstArgumentMuteConverter(int argument) :
        std::invalid_argument("Bad first argument for mute converter : " + std::to_string(argument))
{}

BadSecondArgumentMuteConverter::BadSecondArgumentMuteConverter(int argument) :
        std::invalid_argument("Bad second argument for mute converter : " + std::to_string(argument))
{}

BadFirstArgumentDoubleMixConverter::BadFirstArgumentDoubleMixConverter(int argument) :
        std::invalid_argument("Bad first argument for double mix converter : " + std::to_string(argument))
{}

BadSecondArgumentDoubleMixConverter::BadSecondArgumentDoubleMixConverter(int argument) :
        std::invalid_argument("Non-existent second argument for double mix converter  : " + std::to_string(argument))
{}

RecurringSecondArgumentDoubleMixConverter::RecurringSecondArgumentDoubleMixConverter(int argument) :
        std::invalid_argument("Recurring second argument for double mix converter  : " + std::to_string(argument))
{}
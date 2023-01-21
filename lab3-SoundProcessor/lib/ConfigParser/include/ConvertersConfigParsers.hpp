#include "ConfigParser.hpp"
#include "ConfigParserExceptions.hpp"

class ConverterParser
{
public:
    virtual ConverterParams parseConverterConfig(const std::vector<std::string_view> &&splitLine) = 0;

    virtual ~ConverterParser() = default;
};

class MuteConverterParser :  public ConverterParser
{
public:
    ConverterParams parseConverterConfig(const std::vector<std::string_view> &&splitLine) override;
};

class MixConverterParser : public ConverterParser
{
private:
    int numInputFiles_;
public:
    MixConverterParser(int numInputFiles_);

    ConverterParams parseConverterConfig(const std::vector<std::string_view> &&splitLine) override;
};

class DoubleMixConverterParser : public ConverterParser
{
private:
    int numInputFiles_;
public:
    DoubleMixConverterParser(int numInputFiles_);

    ConverterParams parseConverterConfig(const std::vector<std::string_view> &&splitLine) override;
};
#include "SoundProcessor.hpp"
#include "SoundProcessorExceptions.hpp"

#include <iostream>

namespace
{
    void printHelpInfo()
    {
        std::cout << "\n\t\t\tSound Processor" << std::endl
                  << std::endl
                  << "\t1   argument \t\t--\t '-c' for detecting config file" << std::endl
                  << "\t2   argument \t\t--\t config file path" << std::endl
                  << "\t3   argument \t\t--\t output file path" << std::endl
                  << "\t... argument \t\t--\t input files path" << std::endl
                  << std::endl
                  << "\t\t\tConfig available params:" << std::endl
                  << std::endl
                  << "\tMute file \t\t--\t mute secStart secEnd" << std::endl
                  << "\tMix files \t\t--\t mix $FileNumber secStart" << std::endl
                  << "\tDouble mix files \t--\t dmix $FirstFileNumber $SecondFileNumber" << std::endl
                  << "\tComment \t\t--\t # comment" << std::endl
                  << std::endl;
    }
}

SoundProcessor::SoundProcessor(int &argc, const char **argv)
{
    if (argc == 1)
    {
        std::cout << "No params entered. Enter -h or --help for help" << std::endl;
        throw SoundProcessorExceptions::HelpArgument();
    }
    if (std::string_view(argv[1]) == "-h" || std::string_view(argv[1]) == "--help")
    {
        printHelpInfo();
        throw SoundProcessorExceptions::HelpArgument();
    }

    if (argc < 5)
    {
        throw std::invalid_argument("incorrect number of parameters");
    }
    if (std::string_view(argv[1]) != "-c")
    {
        throw std::invalid_argument("-c Argument was not found");
    }

    configFilePath_ = std::string(argv[2]);
    outputFilePath_ = std::string(argv[3]);

    for (int i = 4; i < argc; ++i)
    {
        inputFilesPaths_.emplace_back(argv[i]);
    }
}

void SoundProcessor::run()
{
    ConfigParser configParser(configFilePath_, inputFilesPaths_.size());

    ConfigParamLine configParams = configParser.getConfig();

    ConverterPipeline pipeline = createPipeline(configParams);

    wavReaderVector_ = createWAVReaderVector();

    WAVWriter wavOutputWriter(outputFilePath_);

    SampleBuffer outputSample {};

    SampleVector defaultSamples(inputFilesPaths_.size());

    while (updateSamples(defaultSamples))
    {
        outputSample = defaultSamples[0];

        for (const auto &converter: pipeline)
        {
            converter->convert(outputSample, defaultSamples);
        }

        wavOutputWriter.writeSample(outputSample);
    }
}

ConverterPipeline SoundProcessor::createPipeline(ConfigParamLine &params)
{
    ConverterPipeline pipeline;

    for (const auto &param: params)
    {
        if (param.converterName_ == "mute")
        {
            pipeline.push_back(MuteConverterCreator().create(param.converterParams_));
        }
        else if (param.converterName_ == "mix")
        {
            pipeline.push_back(MixConverterCreator().create(param.converterParams_));
        }
        else if (param.converterName_ == "dmix")
        {
            if (param.converterParams_.firstParam_ > inputFilesPaths_.size()
                || param.converterParams_.secondParam_ > inputFilesPaths_.size())
            {
                throw std::invalid_argument("bad dmix converter params");
            }

            pipeline.push_back(DoubleMixConverterCreator().create(param.converterParams_));
        }
        else
        {
            // throw exception about invalid convertor name
            throw SoundProcessorExceptions::BadConverterName(param.converterName_);
        }
    }
    return pipeline;
}

WAVReaderVector SoundProcessor::createWAVReaderVector()
{
    WAVReaderVector wavReaderVector;

    for (const auto &inputFilesPath: inputFilesPaths_)
    {
        wavReaderVector.emplace_back(inputFilesPath);
    }

    return wavReaderVector;
}

bool SoundProcessor::updateSamples(SampleVector &defaultSamples)
{
    if (!wavReaderVector_[0].readSample(defaultSamples[0]))
    {
        return false;
    }

    for (int i = 1; i < defaultSamples.size(); ++i)
    {
        wavReaderVector_[i].readSample(defaultSamples[i]);
    }

    return true;
}
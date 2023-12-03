#pragma once

#include <exception>
#include <string>
#include <stdexcept>

namespace WAVExceptions
{
    class BadFileFormat :  public std::invalid_argument
    {
    public:
        explicit BadFileFormat(const std::string& filePath);
    };

    class BadFileOpening : public std::invalid_argument
    {
    public:
        explicit BadFileOpening(const std::string& filePath);
    };

    class BadChunkHeaderFormat :  public std::invalid_argument
    {
    public:
        BadChunkHeaderFormat(const std::string& filePath, uint32_t chunkName);
    };

    class BadFormatHeader : public std::invalid_argument
    {
    public:
        explicit BadFormatHeader(const std::string& filePath);
    };

    class BadFMTChunkDataFormat : public std::invalid_argument
    {
    public:
        explicit BadFMTChunkDataFormat(const std::string& filePath);
    };

    class BadReadingFile :public std::invalid_argument
    {
    public:
        explicit BadReadingFile(const std::string& filePath);
    };

    class BadWritingFile : public std::invalid_argument
    {
    public:
        explicit BadWritingFile(const std::string& filePath);
    };
}
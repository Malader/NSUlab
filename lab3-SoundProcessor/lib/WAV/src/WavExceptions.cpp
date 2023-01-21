#include "WAVExceptions.hpp"

using namespace WAVExceptions;

BadFileFormat::BadFileFormat(const std::string &filePath) :
        std::invalid_argument("Bad file format " + filePath)
{}

BadFileOpening::BadFileOpening(const std::string &filePath) :
        std::invalid_argument("Bad file opening : " + filePath)
{}

BadChunkHeaderFormat::BadChunkHeaderFormat(const std::string &filePath, uint32_t chunkName) :
        std::invalid_argument("Bad " + std::to_string(chunkName) + " chunk format: " + filePath)
{}

BadFormatHeader::BadFormatHeader(const std::string &filePath) :
        std::invalid_argument("Bad header field format : " + filePath)
{}

BadFMTChunkDataFormat::BadFMTChunkDataFormat(const std::string &filePath) :
        std::invalid_argument("Bad FMT chunk data format : " + filePath)
{}

BadReadingFile::BadReadingFile(const std::string &filePath) :
        std::invalid_argument("Bad reading file :" + filePath)
{}

BadWritingFile::BadWritingFile(const std::string &filePath) :
        std::invalid_argument("Bad writing in file " + filePath)
{}
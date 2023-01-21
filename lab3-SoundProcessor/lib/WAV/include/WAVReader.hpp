#pragma once

#include <fstream>
#include <string>

#include "WAVTypes.hpp"

class WAVReader;

using WAVReaderVector = std::vector<WAVReader>;

class WAVReader
{
private:
    std::ifstream inputFile_;

    std::string inputFilePath_;

    void open(std::string filePath);

    void readHeader();

    void readChunk(WAVHeader::Chunk &chunk);

    void readFormat(WAVHeader::format &format);

    void readChunkData(WAVHeader::FMTChunkData &chunkData);

public:
    WAVReader() = default;

    WAVReader(std::string filePath);

    bool readSample(SampleBuffer &sampleBuffer);
};
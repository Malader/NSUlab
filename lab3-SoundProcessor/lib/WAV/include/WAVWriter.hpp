#pragma once

#include <string>
#include <fstream>

#include "WAVTypes.hpp"

class WAVWriter
{
private:
    std::ofstream outputFile_;

    std::string outputFilePath_;

    void writeHeader();

    void writeChunk(WAVHeader::Chunk &chunk);

    void writeFormat(WAVHeader::format &format);

    void writeChunkData(WAVHeader::FMTChunkData &chunkData);

public:
    WAVWriter() = default;

    WAVWriter(const std::string& path);

    ~WAVWriter();

    void fixHeader();

    void writeSample(SampleBuffer);
};
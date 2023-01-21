#include "WAVReader.hpp"

#include "WAVExceptions.hpp"

WAVReader::WAVReader(std::string filePath)
{
    open(std::move(filePath));
}

void WAVReader::open(std::string filePath)
{
    if (filePath.find(".wav") == std::string::npos)
    {
        // WAV exception about not format file
        throw WAVExceptions::BadFileFormat(filePath);
    }
    inputFilePath_ = std::move(filePath);

    inputFile_.open(inputFilePath_, std::ios_base::binary);
    if (!inputFile_.good())
    {
        // WAV exception about bad file opening
        throw WAVExceptions::BadFileOpening(inputFilePath_);
    }

    readHeader();
}

void WAVReader::readHeader()
{
    WAVHeader::Chunk riffChunk {};
    readChunk(riffChunk);

    if (!inputFile_.good() || riffChunk.chunkID != WAVSupportedFormat::RIFF)
    {
        // WAV exception about bad riffChunk format
        throw WAVExceptions::BadChunkHeaderFormat(inputFilePath_, WAVSupportedFormat::RIFF);
    }

    WAVHeader::format format{};
    readFormat(format);

    if (!inputFile_.good() || format != WAVSupportedFormat::WAVE)
    {
        // WAV exception about bad format sym
        throw WAVExceptions::BadFormatHeader(inputFilePath_);
    }

    WAVHeader::Chunk fmtChunk {};
    readChunk(fmtChunk);

    if (!inputFile_.good() || fmtChunk.chunkID != WAVSupportedFormat::FMT_)
    {
        throw WAVExceptions::BadChunkHeaderFormat(inputFilePath_, WAVSupportedFormat::FMT_);
    }

    WAVHeader::FMTChunkData fmtData {};
    readChunkData(fmtData);

    if (!inputFile_.good())
    {
        throw WAVExceptions::BadReadingFile(inputFilePath_);
    }

    if (fmtData.audioFormat != WAVSupportedFormat::AUDIO_FORMAT_PCM ||

        fmtData.numChannels != WAVSupportedFormat::NUM_CHANNELS ||

        fmtData.sampleRate != WAVSupportedFormat::SAMPLE_RATE)
    {
        // WAV excetpion about bad FMT data format
        throw WAVExceptions::BadFMTChunkDataFormat(inputFilePath_);
    }

    WAVHeader::Chunk dataChunk{};
    readChunk(dataChunk);

    while (dataChunk.chunkID != WAVSupportedFormat::DATA)
    {
        if (!inputFile_.good())
        {
            throw WAVExceptions::BadReadingFile(inputFilePath_);
        }

        inputFile_.ignore(dataChunk.chunkSize);
        readChunk(dataChunk);
    }
}

bool WAVReader::readSample(SampleBuffer &sampleBuffer)
{
    inputFile_.read((char *) &sampleBuffer, sizeof(Sample) * sampleBuffer.size());

    if (inputFile_.gcount() == 0)
    {
        sampleBuffer.fill(0);
    }

    return inputFile_.gcount();
}

void WAVReader::readChunk(WAVHeader::Chunk &chunk)
{
    std::array<unsigned char, sizeof(WAVHeader::Chunk)> charBuffer {};
    inputFile_.read((char *) &charBuffer[0], sizeof(charBuffer));

    chunk.chunkID =
            (charBuffer[3] << 24) |
            (charBuffer[2] << 16) |
            (charBuffer[1] << 8) |
            (charBuffer[0]);
    chunk.chunkSize =
            (charBuffer[7] << 24) |
            (charBuffer[6] << 16) |
            (charBuffer[5] << 8) |
            (charBuffer[4]);
}

void WAVReader::readFormat(WAVHeader::format &format)
{
    std::array<unsigned char, sizeof(WAVHeader::format)> charBuffer {};
    inputFile_.read((char *) &charBuffer[0], sizeof(charBuffer));

    format = (charBuffer[3] << 24) |
             (charBuffer[2] << 16) |
             (charBuffer[1] << 8) |
             (charBuffer[0]);
}

void WAVReader::readChunkData(WAVHeader::FMTChunkData &chunkData)
{
    std::array<unsigned char, sizeof(WAVHeader::FMTChunkData)> charBuffer {};
    inputFile_.read((char *) &charBuffer[0], sizeof(charBuffer));

    chunkData.audioFormat =
            (charBuffer[1] << 8) |
            (charBuffer[0]);
    chunkData.numChannels =
            (charBuffer[3] << 8) |
            (charBuffer[2]);
    chunkData.sampleRate =
            (charBuffer[7] << 24) |
            (charBuffer[6] << 16) |
            (charBuffer[5] << 8) |
            (charBuffer[4]);
    chunkData.byteRate =
            (charBuffer[11] << 24) |
            (charBuffer[10] << 16) |
            (charBuffer[9] << 8) |
            (charBuffer[8]);
    chunkData.blockAlign =
            (charBuffer[13] << 8) |
            (charBuffer[12]);
    chunkData.bitsPerSample =
            (charBuffer[15] << 8) |
            (charBuffer[14]);
}



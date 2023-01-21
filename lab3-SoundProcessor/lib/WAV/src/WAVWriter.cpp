#include "WAVWriter.hpp"
#include "WAVExceptions.hpp"

WAVWriter::WAVWriter(const std::string &path)
{
    outputFile_ = std::ofstream(path);
    if (!outputFile_.is_open())
    {
        throw std::invalid_argument("output file was not opened");
    }
    outputFilePath_ = path;
    writeHeader();
}

void WAVWriter::writeHeader()
{
    WAVHeader::Chunk riffChunk =
            {
                    WAVSupportedFormat::RIFF,
                    0
            };

    writeChunk(riffChunk);

    WAVHeader::format format = WAVSupportedFormat::WAVE;

    writeFormat(format);

    WAVHeader::Chunk fmtChunk =
            {
                    WAVSupportedFormat::FMT_,
                    sizeof(WAVHeader::FMTChunkData)
            };

    writeChunk(fmtChunk);

    WAVHeader::FMTChunkData fmtData =
            {
                    WAVSupportedFormat::AUDIO_FORMAT_PCM,
                    WAVSupportedFormat::NUM_CHANNELS,
                    WAVSupportedFormat::SAMPLE_RATE,
                    WAVSupportedFormat::BYTE_RATE,
                    WAVSupportedFormat::BLOCK_ALIGN,
                    WAVSupportedFormat::BITS_PER_SAMPLE
            };

    writeChunkData(fmtData);

    WAVHeader::Chunk dataChunk =
            {
                    WAVSupportedFormat::DATA,
                    0
            };

    writeChunk(dataChunk);
}

void WAVWriter::fixHeader()
{
    outputFile_.seekp(0, std::ios_base::end);
    uint32_t fSize = outputFile_.tellp();

    // Header chunk size
    outputFile_.seekp(
            sizeof(WAVSupportedFormat::RIFF),
            std::ios_base::beg);

    fSize -= sizeof(WAVHeader::Chunk);
    outputFile_.write((char *) &fSize, sizeof(fSize));

    // Data size
    fSize -= sizeof(WAVHeader::format)
             + sizeof(WAVHeader::Chunk)
             + sizeof(WAVHeader::FMTChunkData)
             + sizeof(WAVHeader::Chunk);

    outputFile_.seekp(
            sizeof(WAVHeader::Chunk)
            + sizeof(WAVHeader::format)
            + sizeof(WAVHeader::Chunk)
            + sizeof(WAVHeader::FMTChunkData)
            + sizeof(WAVSupportedFormat::DATA),
            std::ios_base::beg);

    outputFile_.write((char *) &fSize, sizeof(fSize));
}

WAVWriter::~WAVWriter()
{
    fixHeader();
}

void WAVWriter::writeSample(SampleBuffer sampleBuffer)
{
    outputFile_.write((char *) &sampleBuffer, sizeof(Sample) * sampleBuffer.size());

    if (!outputFile_.good())
    {
        throw WAVExceptions::BadWritingFile(outputFilePath_);
    }
}

void WAVWriter::writeChunk(WAVHeader::Chunk &chunk)
{
    std::array<unsigned char, sizeof(WAVHeader::Chunk)> charBuffer {};

    charBuffer[3] = chunk.chunkID >> 24;
    charBuffer[2] = chunk.chunkID >> 16;
    charBuffer[1] = chunk.chunkID >> 8;
    charBuffer[0] = chunk.chunkID;

    charBuffer[7] = chunk.chunkSize >> 24;
    charBuffer[6] = chunk.chunkSize >> 16;
    charBuffer[5] = chunk.chunkSize >> 8;
    charBuffer[4] = chunk.chunkSize;

    outputFile_.write((char *) &charBuffer[0], sizeof(charBuffer));
}

void WAVWriter::writeFormat(WAVHeader::format &format)
{
    std::array<unsigned char, sizeof(WAVHeader::format)> charBuffer {};

    charBuffer[3] = format >> 24;
    charBuffer[2] = format >> 16;
    charBuffer[1] = format >> 8;
    charBuffer[0] = format;

    outputFile_.write((char *) &charBuffer[0], sizeof(charBuffer));
}

void WAVWriter::writeChunkData(WAVHeader::FMTChunkData &chunkData)
{
    std::array<unsigned char, sizeof(WAVHeader::FMTChunkData)> charBuffer {};

    charBuffer[1] = chunkData.audioFormat >> 8;
    charBuffer[0] = chunkData.audioFormat;

    charBuffer[3] = chunkData.numChannels >> 8;
    charBuffer[2] = chunkData.numChannels;

    charBuffer[7] = chunkData.sampleRate >> 24;
    charBuffer[6] = chunkData.sampleRate >> 16;
    charBuffer[5] = chunkData.sampleRate >> 8;
    charBuffer[4] = chunkData.sampleRate;

    charBuffer[11] = chunkData.byteRate >> 24;
    charBuffer[10] = chunkData.byteRate >> 16;
    charBuffer[9] = chunkData.byteRate >> 8;
    charBuffer[8] = chunkData.byteRate;

    charBuffer[13] = chunkData.blockAlign >> 8;
    charBuffer[12] = chunkData.blockAlign;

    charBuffer[15] = chunkData.bitsPerSample >> 8;
    charBuffer[14] = chunkData.bitsPerSample;

    outputFile_.write((char *) &charBuffer[0], sizeof(charBuffer));
}



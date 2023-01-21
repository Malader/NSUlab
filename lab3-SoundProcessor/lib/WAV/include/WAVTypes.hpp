#pragma once

#include <cstdint>
#include <array>
#include <vector>

struct WAVHeader
{
    struct Chunk
    {
        uint32_t chunkID; // symbols "RIFF"

        uint32_t chunkSize; // size of WAV header data without chunkID and chunkSize
    };

    using format = uint32_t; // symbols "WAVE"

    struct FMTChunkData
    {
        uint16_t audioFormat; // audio format

        uint16_t numChannels; // number of channels

        uint32_t sampleRate; // sample rate

        uint32_t byteRate; // bytes rate per second

        uint16_t blockAlign; // number of bytes for one sample

        uint16_t bitsPerSample; // capacity of bits in sample
    };
};

namespace WAVSupportedFormat
{
    static constexpr uint32_t RIFF = 0x46464952;

    static constexpr uint32_t WAVE = 0x45564157;

    static constexpr uint32_t FMT_ = 0x20746d66;

    static constexpr uint32_t DATA = 0x61746164;

    static constexpr uint16_t AUDIO_FORMAT_PCM = 1;

    static constexpr uint16_t NUM_CHANNELS = 1;

    static constexpr uint32_t SAMPLE_RATE = 44100;

    static constexpr uint16_t BITS_PER_BYTE = 8;

    static constexpr uint16_t BITS_PER_SAMPLE = BITS_PER_BYTE * sizeof(int16_t);

    static constexpr uint16_t BLOCK_ALIGN = NUM_CHANNELS * BITS_PER_SAMPLE / BITS_PER_BYTE;

    static constexpr uint32_t BYTE_RATE = BLOCK_ALIGN * SAMPLE_RATE;
}

using Sample = int16_t;
using SampleBuffer = std::array<Sample, WAVSupportedFormat::SAMPLE_RATE>;
using SampleVector = std::vector<SampleBuffer>;
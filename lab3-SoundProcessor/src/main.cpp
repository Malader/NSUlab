#include <iostream>

#include "SoundProcessor.hpp"


int main(int argc, char const *argv[])
{
    try
    {
        SoundProcessor processor(argc, argv);
        processor.run();
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}

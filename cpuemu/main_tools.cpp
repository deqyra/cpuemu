#include "main_tools.hpp"

#include <algorithm>
#include <fstream>
#include <vector>

std::vector<emu::Byte> loadBinFile(std::string path)
{
    std::ifstream binFile(path, std::ios::binary | std::ios::ate);
    std::fstream::pos_type size = binFile.tellg();
    std::vector<emu::Byte> bin((size_t)size);

    std::copy(
        std::istreambuf_iterator<char>(binFile),
        std::istreambuf_iterator<char>(0),
        std::back_inserter(bin)
    );

    return bin;
}

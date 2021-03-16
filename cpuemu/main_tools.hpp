#ifndef CPUEMU__MAIN_TOOLS_HPP
#define CPUEMU__MAIN_TOOLS_HPP

#include <string>
#include <vector>

#include <emu/common/types.hpp>

std::vector<emu::Byte> loadBinFile(std::string path);

#endif//CPUEMU__MAIN_TOOLS_HPP
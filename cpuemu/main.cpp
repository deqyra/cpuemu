#include <iostream>
#include <vector>

#ifdef _WIN32
	#include <windows.h>
#endif//_WIN32

#include <cpuemu/common/types.hpp>
#include <cpuemu/w65c02s/cpu.hpp>

#include "main_tools.hpp"
#include "project_env.hpp"

int main(int argc, char** argv)
{
	#ifdef _WIN32
		SetConsoleOutputCP(65001);
	#endif

    std::cout << PROJECT_NAME << " v" << PROJECT_VERSION << '\n';
    std::cout << COPYRIGHT_NOTICE << '\n';
	std::cout << MIT_LICENSE_NOTICE << '\n' << std::endl;

	using namespace emu;
	using w65c02s::CPU;
	using Ins = w65c02s::Instruction;

	CPU cpu;
	Memory<CPU::MaxMemory> mem;
	std::vector<Byte> Program = {
		(Byte)Ins::LDA_IMM,      	0x02,
		(Byte)Ins::ADC_IMM,			0x03
	};

	constexpr uint16_t StartAddress = 0x0000;

	mem[0xFFFC] = (Byte)(StartAddress & 0x00FF);
	mem[0xFFFD] = (Byte)((StartAddress & 0xFF00) >> 8);
	mem[StartAddress] = Program;

	for (unsigned int i = 0; i < 11; i++)
	{
		if (cpu.rnw) cpu.DB = mem[cpu.AB];

		cpu.tick();
	}

	return EXIT_SUCCESS;
}

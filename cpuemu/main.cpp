#include <iostream>

#ifdef _WIN32
	#include <windows.h>
#endif//_WIN32

#include <emu/common/types.hpp>

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

	return EXIT_SUCCESS;
}

###############################################################################
#                                                                             #
#                             CMake configuration                             #
#                                                                             #
###############################################################################

cmake_minimum_required(VERSION 3.1...3.15)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()



###############################################################################
#                                                                             #
#                                   Toggles                                   #
#                                                                             #
###############################################################################

option(BUILD_STATIC_LIBS "Build libraries as static libraries" OFF)
option(BUILD_RELEASE "Whether to build for a debug or release profile" OFF)

if(${BUILD_STATIC_LIBS} OR WIN32)
    set(STATIC_OR_SHARED "STATIC")
else()
    set(STATIC_OR_SHARED "SHARED")
endif()

if (${BUILD_RELEASE})
    set(CMAKE_BUILD_TYPE "Release")
else()
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# if(WIN32)
#     message(STATUS "Windows detected, forcing static libs.")
#     set(BUILD_STATIC_LIBS ON)
# endif()



###############################################################################
#                                                                             #
#                              Compiler options                               #
#                                                                             #
###############################################################################

set(CMAKE_CXX_STANDARD 20)

if (NOT ${BUILD_RELEASE})
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        # using Clang
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -O0")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
        # using Intel C++
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /Od")
    endif()
endif()

if(CMAKE_COMPILER_IS_GNUCC)
endif()

# set(CMAKE_CXX_COMPILER_WORKS 1)
# Skips the compiler test, which is platform-dependent



###############################################################################
#                                                                             #
#                             Project definition                              #
#                                                                             #
###############################################################################

# Project general info
set(PROJECT_VERSION "1.0")
set(PROJECT_NAME "cpuemu")
set(PROJECT_URL "https://github.com/deqyra/cpuemu")

project(
    ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    DESCRIPTION "A simple CPU emulator"
    LANGUAGES C CXX
)

set(PROJECT_MAINTAINER_NAME "François Brachais")
set(PROJECT_MAINTAINER_EMAIL "deqyra@gmail.com")

# Copyleft notice generation
set(PROJECT_START_YEAR "2021")
set(DATE_SPAN "${PROJECT_START_YEAR}")

string(TIMESTAMP CURRENT_YEAR "%Y")
if(NOT CURRENT_YEAR EQUAL PROJECT_START_YEAR)
    set(DATE_SPAN "${PROJECT_START_YEAR}-${CURRENT_YEAR}")
endif()

set(PROJECT_COPYRIGHT "${DATE_SPAN} © ${PROJECT_MAINTAINER_NAME} <${PROJECT_MAINTAINER_EMAIL}>")

# File configuration
configure_file("${CMAKE_SOURCE_DIR}/cpuemu/config/project_env.config.hpp" "${CMAKE_SOURCE_DIR}/cpuemu/project_env.hpp")



###############################################################################
#                                                                             #
#                            Dependency locations                             #
#                                                                             #
###############################################################################

set(EXPORT_LOCATION ${CMAKE_SOURCE_DIR}/external)
set(EXTERNAL_SOURCE_LOCATION ${CMAKE_SOURCE_DIR}/external/source)
set(CPUEMU_MODULE_LOCATION ${CMAKE_SOURCE_DIR}/cpuemu)
file(MAKE_DIRECTORY ${EXPORT_LOCATION})
file(MAKE_DIRECTORY ${EXPORT_LOCATION}/include)
file(MAKE_DIRECTORY ${EXPORT_LOCATION}/lib)



###############################################################################
#                                                                             #
#                  Target names and file names masterlists                    #
#                                                                             #
###############################################################################
#    (easier to browse here than to go and update it in each subdirectory)    #
###############################################################################

set(CPPTOOLS_LIB_NAME "cpptools")
include(ExternalProject)
ExternalProject_Add(${CPPTOOLS_LIB_NAME}_source
    GIT_REPOSITORY https://github.com/deqyra/CppTools
    CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${EXPORT_LOCATION}
    -DCPPTOOLS_SKIP_TESTS=ON
)

# set(COMPILAX_LIB_NAME "compilax")
# ExternalProject_Add(${COMPILAX_LIB_NAME}_source
#     GIT_REPOSITORY https://github.com/deqyra/CompilaX
#     CMAKE_ARGS
#     -DCMAKE_INSTALL_PREFIX=${EXPORT_LOCATION}
# )

set(EMU_COMMON_LIB_NAME "emucommon")
set(EMU_COMMON_SOURCE_FILES
    env.hpp
    memory.hpp
    types.cpp
    types.hpp
)

set(W65C02S_LIB_NAME "w65c02s")
set(W65C02S_SOURCE_FILES
    cpu.cpp
    cpu.hpp
    execution_wrapper.cpp
    execution_wrapper.hpp
    instruction.hpp
    instruction_info.hpp
    pinout.hpp
    program_sanity_checker.cpp
    program_sanity_checker.hpp
    register_view.hpp
)



###############################################################################
#                                                                             #
#                           Include subdirectories                            #
#                                                                             #
###############################################################################

# Import targets for common files
add_subdirectory(${CPUEMU_MODULE_LOCATION}/common ${CMAKE_BINARY_DIR}/${EMU_COMMON_LIB_NAME})

# Import targets for MOS 6502
add_subdirectory(${CPUEMU_MODULE_LOCATION}/w65c02s ${CMAKE_BINARY_DIR}/${W65C02S_LIB_NAME})



###############################################################################
#                                                                             #
#                           Build cpuemu executable                           #
#                                                                             #
###############################################################################

# Build executable
add_executable("cpuemu"
    ${CPUEMU_MODULE_LOCATION}/main.cpp
    ${CPUEMU_MODULE_LOCATION}/main_tools.hpp
    ${CPUEMU_MODULE_LOCATION}/main_tools.cpp
    ${CPUEMU_MODULE_LOCATION}/project_env.hpp
)   

add_dependencies("cpuemu"
    ${CPPTOOLS_LIB_NAME}_source
    "export_${EMU_COMMON_LIB_NAME}_headers"
    "export_${EMU_COMMON_LIB_NAME}_lib"
    "export_${W65C02S_LIB_NAME}_headers"
    "export_${W65C02S_LIB_NAME}_lib"
)

target_include_directories("cpuemu" PUBLIC
    ${EXPORT_LOCATION}/include
)
target_link_directories("cpuemu" PUBLIC
    ${EXPORT_LOCATION}/lib
)

target_link_libraries("cpuemu" PUBLIC ${CMAKE_DL_LIBS}
    ${CPPTOOLS_LIB_NAME}
    ${EMU_COMMON_LIB_NAME}
    ${W65C02S_LIB_NAME}
) 

add_custom_command(TARGET "cpuemu" POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${EXPORT_LOCATION}/lib" $<TARGET_FILE_DIR:cpuemu>
)



###############################################################################
#                                                                             #
#                                    Tests                                    #
#                                                                             #
###############################################################################

# Build and run tests
enable_testing()
set(TEST_TARGET_NAME emutests)
add_executable(${TEST_TARGET_NAME}
    tests/main.cpp
    tests/common/test_memory.cpp
    tests/w65c02s/test_program_sanity_checker.cpp
    tests/w65c02s/test_execution_wrapper.cpp
    tests/w65c02s/instructions/arithmetic/test_adc.cpp
)
add_dependencies(${TEST_TARGET_NAME} "cpuemu")
target_link_libraries(${TEST_TARGET_NAME} PUBLIC
    ${EMU_COMMON_LIB_NAME}
    ${W65C02S_LIB_NAME}
    ${CPPTOOLS_LIB_NAME}
)

add_test(NAME "tests" COMMAND ${TEST_TARGET_NAME})
add_custom_command(TARGET ${TEST_TARGET_NAME}
                   COMMENT "Running tests"
                   POST_BUILD
                   COMMAND "$<TARGET_FILE:${TEST_TARGET_NAME}>")

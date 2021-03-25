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
    -DCPPTOOLS_EXTERNAL_INSTALL_PREFIX=True
    -DCPPTOOLS_SKIP_TESTS=ON
)

set(EMU_COMMON_LIB_NAME "emucommon")
set(EMU_COMMON_SOURCE_FILES
    env.hpp
    memory.hpp
    types.cpp
    types.hpp
)

set(MOS6502_LIB_NAME "mos6502")
set(MOS6502_SOURCE_FILES
    cpu.cpp
    cpu.hpp
    instruction.hpp
    instruction_impl.hpp
    instruction_impl/addressing_mode.hpp
    instruction_impl/common.cpp
    instruction_impl/common.hpp
    instruction_impl/arithmetic/adc.cpp
    instruction_impl/arithmetic/cmp.cpp
    instruction_impl/arithmetic/cpx.cpp
    instruction_impl/arithmetic/cpy.cpp
    instruction_impl/arithmetic/sbc.cpp
    instruction_impl/bit/rmb.cpp
    instruction_impl/bit/smb.cpp
    instruction_impl/bit/trb.cpp
    instruction_impl/bit/tsb.cpp
    instruction_impl/branches/bbr.cpp
    instruction_impl/branches/bbs.cpp
    instruction_impl/branches/bcc.cpp
    instruction_impl/branches/bcs.cpp
    instruction_impl/branches/beq.cpp
    instruction_impl/branches/bmi.cpp
    instruction_impl/branches/bne.cpp
    instruction_impl/branches/bpl.cpp
    instruction_impl/branches/bra.cpp
    instruction_impl/branches/bvc.cpp
    instruction_impl/branches/bvs.cpp
    instruction_impl/incdec/dec.cpp
    instruction_impl/incdec/dex.cpp
    instruction_impl/incdec/dey.cpp
    instruction_impl/incdec/inc.cpp
    instruction_impl/incdec/inx.cpp
    instruction_impl/incdec/iny.cpp
    instruction_impl/jumps/jmp.cpp
    instruction_impl/jumps/jsr.cpp
    instruction_impl/jumps/rts.cpp
    instruction_impl/ldst/lda.cpp
    instruction_impl/ldst/ldx.cpp
    instruction_impl/ldst/ldy.cpp
    instruction_impl/ldst/sta.cpp
    instruction_impl/ldst/stx.cpp
    instruction_impl/ldst/sty.cpp
    instruction_impl/ldst/stz.cpp
    instruction_impl/logical/and.cpp
    instruction_impl/logical/bit.cpp
    instruction_impl/logical/eor.cpp
    instruction_impl/logical/ora.cpp
    instruction_impl/regtransfer/tax.cpp
    instruction_impl/regtransfer/tay.cpp
    instruction_impl/regtransfer/txa.cpp
    instruction_impl/regtransfer/tya.cpp
    instruction_impl/shifts/asl.cpp
    instruction_impl/shifts/lsr.cpp
    instruction_impl/shifts/rol.cpp
    instruction_impl/shifts/ror.cpp
    instruction_impl/stack/pha.cpp
    instruction_impl/stack/php.cpp
    instruction_impl/stack/phx.cpp
    instruction_impl/stack/phy.cpp
    instruction_impl/stack/pla.cpp
    instruction_impl/stack/plp.cpp
    instruction_impl/stack/plx.cpp
    instruction_impl/stack/ply.cpp
    instruction_impl/stack/tsx.cpp
    instruction_impl/stack/txs.cpp
    instruction_impl/status/clc.cpp
    instruction_impl/status/cld.cpp
    instruction_impl/status/cli.cpp
    instruction_impl/status/clv.cpp
    instruction_impl/status/sec.cpp
    instruction_impl/status/sed.cpp
    instruction_impl/status/sei.cpp
    instruction_impl/system/brk.cpp
    instruction_impl/system/nop.cpp
    instruction_impl/system/rti.cpp
    instruction_impl/system/stp.cpp
    instruction_impl/system/wai.cpp
)



###############################################################################
#                                                                             #
#                           Include subdirectories                            #
#                                                                             #
###############################################################################

# Import targets for common files
add_subdirectory(${CPUEMU_MODULE_LOCATION}/common ${CMAKE_BINARY_DIR}/${EMU_COMMON_LIB_NAME})

# Import targets for MOS 6502
add_subdirectory(${CPUEMU_MODULE_LOCATION}/mos6502 ${CMAKE_BINARY_DIR}/${MOS6502_LIB_NAME})



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
    "export_${MOS6502_LIB_NAME}_headers"
    "export_${MOS6502_LIB_NAME}_lib"
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
    ${MOS6502_LIB_NAME}
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
# enable_testing()
# add_executable(${TEST_TARGET_NAME})
# target_link_libraries(${TEST_TARGET_NAME} PUBLIC "RenderBoi.Core" ${CPPTOOLS_LIB_NAME})
# add_dependencies(${TEST_TARGET_NAME} "copy_assets" "copy_dlls")

# add_test(NAME "tests" COMMAND ${TEST_TARGET_NAME})
# add_custom_command(TARGET ${TEST_TARGET_NAME}
#                    COMMENT "Running tests"
#                    POST_BUILD
#                    COMMAND "./tests")

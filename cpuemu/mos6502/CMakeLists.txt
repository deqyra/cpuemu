# Generate script file to copy headers
file(WRITE ${CMAKE_BINARY_DIR}/cp_${MOS6502_LIB_NAME}_headers.cmake
    "file(COPY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION ${EXPORT_LOCATION}/include/cpuemu
        FILES_MATCHING
        PATTERN \"*.hpp\"
   )\n"
)

# Build window lib
add_library(${MOS6502_LIB_NAME} ${STATIC_OR_SHARED}
    ${MOS6502_SOURCE_FILES}
)

add_dependencies(${MOS6502_LIB_NAME}
    "export_${EMU_COMMON_LIB_NAME}_lib"
    "export_${EMU_COMMON_LIB_NAME}_headers"
)

target_include_directories(${MOS6502_LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/cpuemu)
target_include_directories(${MOS6502_LIB_NAME} PUBLIC ${EXPORT_LOCATION}/include)
target_link_directories(${MOS6502_LIB_NAME} PUBLIC ${EXPORT_LOCATION}/lib)

target_link_libraries(${MOS6502_LIB_NAME} PUBLIC ${CMAKE_DL_LIBS}
    ${EMU_COMMON_LIB_NAME}
)

# Custom target to export window lib
add_custom_target("export_${MOS6502_LIB_NAME}_lib")
add_dependencies("export_${MOS6502_LIB_NAME}_lib" ${MOS6502_LIB_NAME})
add_custom_command(
    TARGET "export_${MOS6502_LIB_NAME}_lib"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${MOS6502_LIB_NAME}> ${EXPORT_LOCATION}/lib
)

# Custom target to export window headers
add_custom_target("export_${MOS6502_LIB_NAME}_headers")
add_custom_command(
    TARGET "export_${MOS6502_LIB_NAME}_headers"
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cp_${MOS6502_LIB_NAME}_headers.cmake
)

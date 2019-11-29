cmake_minimum_required(VERSION 3.0)

#-----------------------------------------------------------------------------#

set(TARGET testbench)
set(SOURCES test.c ../src/crc32.c)
add_executable(${TARGET} ${SOURCES})
target_include_directories(${TARGET} PUBLIC ../include)

#-----------------------------------------------------------------------------#
target_compile_options(${TARGET} PUBLIC -std=gnu11
										-Wall
										-Werror
										-O2
)
#-----------------------------------------------------------------------------#
install(TARGETS ${TARGET} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
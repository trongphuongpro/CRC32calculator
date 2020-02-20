cmake_minimum_required(VERSION 3.0)

set(TARGET crc32)

#-----------------------------------------------------------------------------#

if (FAMILY STREQUAL AVR)
	add_library(${TARGET} STATIC src/crc32_atmega.c)

elseif (FAMILY STREQUAL TIVA)
	add_library(${TARGET} STATIC src/crc32_tiva.c)

else()
	message(">> Failure due to missing FAMILY.")

endif()

target_include_directories(${TARGET} PUBLIC include)

#-----------------------------------------------------------------------------#

if (FAMILY STREQUAL AVR)
	target_compile_options(${TARGET} PUBLIC -mmcu=${MCU}
											-std=gnu11
											-O2
											-Wall
											-Werror
	)

	target_compile_definitions(${TARGET} PUBLIC F_CPU=${F_CPU})

#-----------------------------------------------------------------------------#

elseif (FAMILY STREQUAL TIVA)

	target_compile_options(${TARGET} PUBLIC -mthumb
											${CPU}
											${FPU}
											${FLOAT}
											-ffunction-sections 
											-fdata-sections    
											-MD                                         
											-pedantic           
											-std=gnu11
											-O2
											-Wall
											-Werror
	)

	target_compile_definitions(${TARGET} PUBLIC TARGET_IS_${REV}
												PART_${MCU}
	)

#-----------------------------------------------------------------------------#

else()
	message(">> Failure due to missing FAMILY.")

endif()
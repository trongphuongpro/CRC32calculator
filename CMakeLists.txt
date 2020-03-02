cmake_minimum_required(VERSION 3.0)

set(TARGET crc32)

#-----------------------------------------------------------------------------#

if (SERIES STREQUAL ATMEGA)
	add_library(${TARGET} STATIC src/crc32_atmega.c)

elseif (SERIES STREQUAL TIVA)
	add_library(${TARGET} STATIC src/crc32_tiva.c)

else()
	message(">> Failure due to missing SERIES.")

endif()

target_include_directories(${TARGET} PUBLIC include)

#-----------------------------------------------------------------------------#

if (SERIES STREQUAL ATMEGA)
	target_compile_options(${TARGET} PUBLIC -mmcu=${MCU}
											-std=gnu11
											-O2
											-Wall
											-Werror
	)

	target_compile_definitions(${TARGET} PUBLIC F_CPU=${F_CPU})

#-----------------------------------------------------------------------------#

elseif (SERIES STREQUAL TIVA)

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
	message(">> Failure due to missing SERIES.")

endif()
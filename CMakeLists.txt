cmake_minimum_required(VERSION 3.8)

project(astro)

set(CMAKE_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)
set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/build")

set(SDL2_LIB_DIR C:/SDL2/lib)
set(SDL2_INCLUDE_DIR C:/SDL2/include)
set(SDL2_LIBRARY C:/SDL2/bin)

include_directories(
	"source"
    ${SDL2_INCLUDE_DIR}
)

link_directories(
    ${SDL2_LIB_DIR}
)

# INCLUDE FILES THAT SHOULD BE COMPILED:
file(GLOB_RECURSE SRC 
	"source/*.cpp" 
	"source/*.hh"
	"source/*.hpp" 
	
	"source/*.c" 
	"source/*.h"
)
add_executable(${PROJECT_NAME} 
	${SRC}
)

# Use C++20
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
if (MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC "/Zc:__cplusplus")
else ()
	target_compile_options(${PROJECT_NAME} PRIVATE 
		# Options for GCC (in order to have warnings)
		-Wall 
		-Wextra 
		# -Wconversion
		-Wno-unused-function
		-Wno-unused-variable
		-Wno-unknown-pragmas
		-Wno-error
	)

	target_link_libraries(
	${PROJECT_NAME}
		mingw32
		SDL2main
		SDL2
		SDL2_image
	)
endif()

# Copy dependencies
file(GLOB PROJECT_DEPENDENCIES ${SDL2_LIBRARY}/*.dll)
foreach(Dependency IN LISTS PROJECT_DEPENDENCIES)
    file(
        COPY ${Dependency}
        DESTINATION ${OUTPUT_DIR}
    )
endforeach()

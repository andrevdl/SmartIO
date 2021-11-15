# CMakeList.txt : CMake project for SmartIO, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSIO_DEBUG")

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/src
	#${CMAKE_CURRENT_SOURCE_DIR}/parser/ast
)

file(GLOB SmartIO_Src
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"

	# Parser
	"${CMAKE_CURRENT_SOURCE_DIR}/src/parser/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/parser/ast/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/parser/dfa/*.cpp"

	#Compiler
	"${CMAKE_CURRENT_SOURCE_DIR}/src/compiler/*.cpp"

	#Debugger
	"${CMAKE_CURRENT_SOURCE_DIR}/src/debugger/*.cpp"
)

# Add source to this project's executable.
add_executable (SmartIO "SmartIO.cpp" "SmartIO.h" ${SmartIO_Src})

target_include_directories(SmartIO PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# TODO: Add tests and install targets if needed.

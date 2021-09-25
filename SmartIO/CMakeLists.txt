# CMakeList.txt : CMake project for SmartIO, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (SmartIO "SmartIO.cpp" "SmartIO.h" "SIOTokenizer.cpp" "SIOTokenizer.h" "SIOTokens.h" "SIOStream.h" "SIOCommon.h" "SIOStream.cpp")

# TODO: Add tests and install targets if needed.

# CMakeList.txt : CMake project for SmartIO, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSIO_DEBUG")

# Add source to this project's executable.
add_executable (SmartIO "SmartIO.cpp" "SmartIO.h" "SIOTokenizer.cpp" "SIOTokenizer.h" "SIOTokens.h" "SIOStream.h" "SIOCommon.h" "SIOStream.cpp" "SIOParser.cpp" "SIOParser.h" "SIONodes/SIONExpr.h" "SIONodes/SIONode.h" "SIONodes/SIONCommon.h" "SIONodes/SIONExpr.cpp" "SIONodes/SIONode.cpp" "SIOTokenWalker.cpp" "SIOTokenWalker.h" "SIONodes/SIONProgram.cpp" "SIONodes/SIONProgram.h" "SIONodes/SIONIdentifier.cpp" "SIONodes/SIONIdentifier.h" "SIONodes/SIONLogicExpr.cpp" "SIONodes/SIONLogicExpr.h" "SIONodes/SIONStmt.cpp" "SIONodes/SIONStmt.h" "SIOStringMapper.h" "SIOStringMapper.cpp" "Debugger/SIODotDebugger.cpp" "Debugger/SIODotDebugger.h")

# TODO: Add tests and install targets if needed.

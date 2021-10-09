# CMakeList.txt : CMake project for SmartIO, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSIO_DEBUG")

# Add source to this project's executable.
add_executable (SmartIO "SmartIO.cpp" "SmartIO.h" "SIOTokenizer.cpp" "SIOTokenizer.h" "SIOTokens.h" "SIOStream.h" "SIOCommon.h" "SIOStream.cpp" "SIOParser.cpp" "SIOParser.h" "Parser/sio_expr.h"  "Parser/sio_common.h" "Parser/sio_expr.cpp"  "SIOTokenWalker.cpp" "SIOTokenWalker.h" "Parser/sio_program.cpp" "Parser/sio_program.h" "Parser/sio_id.cpp" "Parser/sio_id.h" "Parser/sio_logic_expr.cpp" "Parser/sio_logic_expr.h" "Parser/sio_stmt.cpp" "Parser/sio_stmt.h" "internal/SIOStringMapper.h" "internal/SIOStringMapper.cpp" "Debugger/SIODotDebugger.cpp" "Debugger/SIODotDebugger.h" "internal/sio_context.cpp" "internal/sio_context.h" "internal/sio_data.h" "internal/sio_define.h")

# TODO: Add tests and install targets if needed.

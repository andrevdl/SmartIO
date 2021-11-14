# CMakeList.txt : CMake project for SmartIO, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSIO_DEBUG")

# Add source to this project's executable.
add_executable (SmartIO "SmartIO.cpp" "SmartIO.h" "parser/SIOTokenizer.cpp" "parser/SIOTokenizer.h" "parser/SIOTokens.h" "SIOStream.h"  "SIOStream.cpp" "parser/SIOParser.cpp" "parser/SIOParser.h" "parser/tree/sio_expr.h"  "parser/tree/sio_tree.h" "parser/tree/sio_expr.cpp"  "parser/SIOTokenWalker.cpp" "parser/SIOTokenWalker.h" "Parser/sio_program.cpp" "Parser/sio_program.h" "parser/tree/sio_id.cpp" "parser/tree/sio_id.h"   "parser/tree/sio_stmt.cpp" "parser/tree/sio_stmt.h"   "Debugger/SIODotDebugger.cpp" "Debugger/SIODotDebugger.h" "internal/sio_context.cpp" "internal/sio_context.h" "internal/sio_data.h" "internal/sio_define.h" "parser/ast/sio_ast.h" "parser/sio_debug_win.h" "internal/sio_memory.h"  "compiler/ir_emiter.h" "compiler/asm_emiter.h")

# TODO: Add tests and install targets if needed.

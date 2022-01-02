cmake_minimum_required (VERSION 3.8)

project ("SmartIO")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSIO_DEBUG")

# Add all source code to the project
file(GLOB SmartIO_Src
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/util/*.cpp"

	# Parser
	"${CMAKE_CURRENT_SOURCE_DIR}/src/parser/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/parser/ast/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/parser/dfa/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/parser/util/*.cpp"

	#Compiler
	"${CMAKE_CURRENT_SOURCE_DIR}/src/compiler/*.cpp"
	
	#Debugger
	"${CMAKE_CURRENT_SOURCE_DIR}/src/debugger/*.cpp"

	#Runtime
	"${CMAKE_CURRENT_SOURCE_DIR}/src/runtime/*.cpp"
)

add_subdirectory(libs)

# Register static lib libffi
add_library(libffi STATIC IMPORTED)
set_target_properties(libffi PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/libffi/libffi-8.lib)

# Add source to this project's executable.
add_executable (SmartIO "SmartIO.cpp" "SmartIO.h" ${SmartIO_Src})
target_include_directories(SmartIO PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_features(SmartIO PUBLIC cxx_std_23)

# Link libffi
target_link_libraries(SmartIO libffi)
target_include_directories(libffi INTERFACE ${CMAKE_CURRENT_LIST_DIR}/libs/libffi/includes)

target_link_libraries(SmartIO fmt::fmt)

# After build, copy the DDL to the output folder
add_custom_command(TARGET SmartIO POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/libs/libffi/libffi-8.dll ${CMAKE_CURRENT_BINARY_DIR}/libffi-8.dll)

# TODO: Add tests and install targets if needed.
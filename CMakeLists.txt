cmake_minimum_required(VERSION 3.15)

project(VirtualDevice)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

file(GLOB SOURCE_FILE src/*.cpp)
file(GLOB HEADER_FILE include/*.h)

add_executable(VirtualDevice ${SOURCE_FILE} ${HEADER_FILE})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

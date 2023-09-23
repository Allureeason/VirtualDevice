cmake_minimum_required(VERSION 3.15)

project(VirtualDevice)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB SOURCE_FILE src/*.cpp)
file(GLOB HEADER_FILE include/*.h)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(LINK_LIBS
    pthread
)

add_executable(VirtualDevice ${SOURCE_FILE} ${HEADER_FILE})
target_link_libraries(VirtualDevice ${LINK_LIBS})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

cmake_minimum_required(VERSION 3.27)
project(Vector C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(Vector STATIC
        src/VecIO.c
        src/Vector.c
)

add_executable(Test test/test.c)
target_compile_options(Test PRIVATE -O1)
target_link_libraries(Test Vector)
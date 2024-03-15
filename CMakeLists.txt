cmake_minimum_required(VERSION 3.27)
project(Containers C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_compile_options(-O3)

add_library(Containers STATIC
        src/Vector.c
        src/String.c
        include/Containers/String.h
        src/Container.c
        include/Containers/Vector.h
        include/Containers/Container.h
        include/Containers/def.h
)

add_executable(Test test/test.c)
target_link_libraries(Test Containers)
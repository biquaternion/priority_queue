cmake_minimum_required(VERSION 3.12)
project(priority_queue C)

set(CMAKE_C_STANDARD 99)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(pqlib
                include/priority_queue.h
                src/priority_queue.c)

add_executable(priority_queue
        main.c)

target_link_libraries(priority_queue pqlib)
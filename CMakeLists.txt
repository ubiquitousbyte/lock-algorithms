cmake_minimum_required(VERSION 3.17)
project(lock_algorithms C)

set(CMAKE_C_STANDARD 99)
find_package(Threads REQUIRED)

add_executable(one-lock-algorithm main.c inc/LockOne.h LockOne.c)
target_link_libraries(one-lock-algorithm ${CMAKE_THREAD_LIBS_INIT})

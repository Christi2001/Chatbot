cmake_minimum_required(VERSION 3.0)

project(chatbot)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS "-std=c99 -fdump-rtl-expand")

include_directories(unity/include)

add_executable(chatbot main.c processing.c appointments.c)

add_executable(unit_tests unit_tests.c processing.c appointments.c main.c unity/src/unity.c)
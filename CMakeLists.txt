cmake_minimum_required(VERSION 3.8)
project(Project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES TM4C123.cpp TM4C123.h)
add_library(Project ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.5)

project(FifoQueue)

set(SOURCE_LIB FifoQueue.cpp)

add_library(FifoQueue STATIC ${SOURCE_LIB})
cmake_minimum_required(VERSION 3.10)
project(DoublyLinkedList)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create object file since OJ will provide main function
add_library(code OBJECT main.cpp)

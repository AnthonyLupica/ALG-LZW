# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(lzw435)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Set the source files for the project
set(SOURCE_FILES main.cpp)

# Add an executable target named lzw435
add_executable(lzw435 ${SOURCE_FILES})

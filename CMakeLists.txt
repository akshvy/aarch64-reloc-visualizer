cmake_minimum_required(VERSION 3.10)
project(AArch64RelocVisualizer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the headers folder
include_directories(include)

# Tell CMake to build our executable from the main.cpp file
add_executable(reloc_vis src/main.cpp src/reloc_engine.cpp)
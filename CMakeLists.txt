cmake_minimum_required(VERSION 4.2)

set(CMAKE_CXX_STANDARD 20)

project (vision)

add_executable(vision
    src/main.cpp
    src/enhancements.cpp
    src/enhancements.h
    src/GaussianFilter.cpp
    src/GaussianFilter.h
    src/imgOps.cpp
    src/imgOps.h
    src/rotate.cpp
    src/rotate.h
    src/scale.cpp
    src/scale.h
    src/similarity.cpp
    src/similarity.h
    src/translate.cpp
    src/translate.h)

include_directories(vision "/opt/homebrew/Cellar/opencv/4.12.0_19/include/opencv4")

# Include current folder to be able to include argparse.hpp from main dir.
include_directories(vision "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(OpenCV REQUIRED)
target_link_libraries(vision ${OpenCV_LIBS}) 

target_compile_options(vision PRIVATE -Wall -Wextra -Wpedantic)

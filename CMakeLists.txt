cmake_minimum_required(VERSION 4.2)

set(CMAKE_CXX_STANDARD 20)

project (vision)

add_executable(vision
    main.cpp
    enhancements.cpp
    enhancements.h
    GaussianFilter.cpp
    GaussianFilter.h
    imgOps.cpp
    imgOps.h
    rotate.cpp
    rotate.h
    scale.cpp
    scale.h
    similarity.cpp
    similarity.h
    translate.cpp
    translate.h)

include_directories(vision "/opt/homebrew/Cellar/opencv/4.12.0_19/include/opencv4")

find_package(OpenCV REQUIRED)
target_link_libraries(vision ${OpenCV_LIBS}) 

target_compile_options(vision PRIVATE -Wall -Wextra -Wpedantic)

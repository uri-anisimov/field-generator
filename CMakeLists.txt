cmake_minimum_required(VERSION 3.10)

project(field-generator)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(bgr2hsv)
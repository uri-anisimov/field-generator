cmake_minimum_required(VERSION 3.10)
project(bgr2hsv)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(bgr2hsvTest test.cpp)
target_link_libraries(bgr2hsvTest ${GTEST_LIBRARIES})

add_executable(bgr2hsv main.cpp)
target_link_libraries(bgr2hsv ${OpenCV_LIBS})

add_executable(visualize visualize.cpp)
target_link_libraries(visualize ${OpenCV_LIBS})

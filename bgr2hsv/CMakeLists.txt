add_executable(bgr2hsvTest test.cpp)
target_link_libraries(bgr2hsvTest ${GTEST_LIBRARIES})

add_executable(bgr2hsv main.cpp)
target_link_libraries(bgr2hsv ${OpenCV_LIBS})

add_executable(visualize visualize.cpp)
target_link_libraries(visualize ${OpenCV_LIBS})

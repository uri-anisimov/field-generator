add_executable(bgr2hsvTest test.cpp)
target_link_libraries(bgr2hsvTest ${GTEST_LIBRARIES} pthread)
install(TARGETS bgr2hsvTests DESTINATION bin)

add_executable(bgr2hsv main.cpp)
target_link_libraries(bgr2hsv ${OpenCV_LIBS})
install(TARGETS bgr2hsv DESTINATION bin)

add_executable(visualize visualize.cpp)
target_link_libraries(visualize ${OpenCV_LIBS})
install(TARGETS visualize DESTINATION bin)

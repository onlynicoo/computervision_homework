cmake_minimum_required(VERSION 2.8)


project(homework_4_CV)
find_package(OpenCV REQUIRED)
include_directories($(OpenCV_INCLUDE_DIRS))

add_executable(task1 src/task1.cpp)
add_executable(task3 src/task3.cpp)
add_executable(task4 src/task4.cpp)
target_link_libraries(task1 ${OpenCV_LIBS})
target_link_libraries(task3 ${OpenCV_LIBS})
target_link_libraries(task4 ${OpenCV_LIBS})

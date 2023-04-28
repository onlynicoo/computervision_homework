#cmake_minimum_required(VERSION 2.8)


project(Lab_5_Segmentation-20230417)
find_package(OpenCV REQUIRED)
include_directories($(OpenCV_INCLUDE_DIRS))

add_executable(task1 src/task1.cpp)
target_link_libraries(task1 ${OpenCV_LIBS})

add_executable(task2 src/task2.cpp)
target_link_libraries(task2 ${OpenCV_LIBS})

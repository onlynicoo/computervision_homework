cmake_minimum_required(VERSION  2.8.12)

project(homework_5_CV)

find_package(OpenCV REQUIRED)
include_directories($(OpenCV_INCLUDE_DIRS))

add_library(utilities_functions
    include/utilities_functions.h
    src/utilities_functions.cpp
)

add_executable( task1
    src/task1.cpp
)
add_executable( task2
    src/task2.cpp
)
add_executable( task3
    src/task3.cpp
)

target_link_libraries(task1 utilities_functions)
target_link_libraries(task2 utilities_functions)
target_link_libraries(task3 utilities_functions)

target_link_libraries(utilities_functions ${OpenCV_LIBS})
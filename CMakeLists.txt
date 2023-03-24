cmake_minimum_required(VERSION 3.2)

project(capture)

# find package 
find_package(OpenCV)


# add include directories
include_directories(${OpenCV_INCLUDE_DIRS})

# add executive file
add_executable(capture ${PROJECT_SOURCE_DIR} capture.cpp)
target_link_libraries(capture ${OpenCV_LIBS})
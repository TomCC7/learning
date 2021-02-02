project(test)

cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
# directory of opencv headers
include_directories(${OpenCV_INCLUDE_DIRS})
# name of executable file and path of source file
add_executable(${PROJECT_NAME} main.cpp)
# directory of opencv library
link_directories(${OpenCV_LIBRARY_DIRS})
add_subdirectory(histogram)
# opencv libraries
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} histogram)
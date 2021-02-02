aux_source_directory(. DIR_SRCS)
add_library(histogram ${DIR_SRCS})

find_package(OpenCV REQUIRED)
# directory of opencv headers
include_directories(${OpenCV_INCLUDE_DIRS})
# directory of opencv library
link_directories(${OpenCV_LIBRARY_DIRS})
# opencv libraries
target_link_libraries(histogram ${OpenCV_LIBS})
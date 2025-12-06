cmake_minimum_required(VERSION 3.25)

find_package(OpenCV REQUIRED core highgui imgproc imgcodecs photo stitching videoio)

link_libraries(${OpenCV_LIBS})

set(CMAKE_CXX_STANDARD 23)

add_executable(calculateEdgesCPU
    calculateEdgesCPU.cpp
)

target_link_libraries(calculateEdgesCPU PRIVATE measurement)

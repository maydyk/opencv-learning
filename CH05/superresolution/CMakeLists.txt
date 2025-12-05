cmake_minimum_required(VERSION 3.25)

find_package(OpenCV REQUIRED core features2d highgui imgproc videoio superres)

link_libraries(${OpenCV_LIBS})

# set(CMAKE_CXX_STANDARD 23)

add_executable(superresolution
    superresolution.cpp
)

cmake_minimum_required(VERSION 3.25)

find_package(OpenCV REQUIRED core imgproc highgui)

link_libraries(${OpenCV_LIBS})

add_executable(Skew
    main.cpp
)
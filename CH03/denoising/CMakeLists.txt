cmake_minimum_required(VERSION 3.25)

find_package(OpenCV REQUIRED core imgproc highgui photo)

link_libraries(${OpenCV_LIBS})

add_executable(denoising
    main.cpp
)
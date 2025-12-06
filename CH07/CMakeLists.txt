cmake_minimum_required(VERSION 3.25)

# Custom performance measurement
add_subdirectory(utils)

# NOTE: Install OpenCL to your system and rebuild OpenCV.

add_subdirectory(checkOpenCL)

add_subdirectory(calculateEdgesCPU)

add_subdirectory(calculateEdgesGPU)

add_subdirectory(detectFaces)

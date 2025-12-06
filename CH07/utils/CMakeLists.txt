cmake_minimum_required(VERSION 3.25)

add_library(measurement STATIC
    measurement.cpp)

target_include_directories(measurement PUBLIC ./)
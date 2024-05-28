cmake_minimum_required(VERSION 3.27.4)
project(Httpino CXX)

add_library(httpino src/httpino.cpp)
target_link_arduino_libraries(httpino PRIVATE core WiFiS3)

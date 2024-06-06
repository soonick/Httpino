cmake_minimum_required(VERSION 3.27.4)
project(Httpino CXX)

add_library(SimpleVector INTERFACE)
target_include_directories(SimpleVector INTERFACE deps/SimpleVector/src)

add_library(ArduinoHashtable INTERFACE)
target_include_directories(ArduinoHashtable INTERFACE deps/ArduinoHashtable/src)
target_link_libraries(ArduinoHashtable INTERFACE SimpleVector)

add_library(httpino src/httpino.cpp)
target_link_arduino_libraries(httpino PRIVATE core WiFiS3)
target_link_libraries(httpino PRIVATE ArduinoHashtable)
target_include_directories(httpino PRIVATE include)

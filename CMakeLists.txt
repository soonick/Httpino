cmake_minimum_required(VERSION 3.27.4)
project(httpino
  VERSION 0.1.0
  LANGUAGES CXX)

add_library(SimpleVector "deps/SimpleVector/src")
target_link_arduino_libraries(SimpleVector PUBLIC core)
target_include_directories(SimpleVector PUBLIC "deps/SimpleVector/src")

add_library(ArduinoHashtable "deps/ArduinoHashtable/src")
target_link_arduino_libraries(ArduinoHashtable PUBLIC core)
target_link_libraries(ArduinoHashtable PUBLIC SimpleVector)
target_include_directories(ArduinoHashtable PUBLIC "deps/ArduinoHashtable/src")

add_library(httpino "src/httpino.cpp")
target_link_arduino_libraries(httpino PUBLIC
  core
  WiFiS3)
target_link_libraries(httpino PUBLIC ArduinoHashtable)
target_include_directories(httpino PUBLIC "include")

cmake_minimum_required(VERSION 3.5)

project(Adafruit_BusIO)

add_library(Adafruit_BusIO STATIC
    Adafruit_I2CDevice.cpp
)

# Inherit the include directories from the Pico SDK
target_link_libraries(Adafruit_BusIO pico_stdlib hardware_i2c)
target_include_directories(Adafruit_BusIO PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


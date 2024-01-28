cmake_minimum_required(VERSION 3.17)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(hello-pico-ros)

pico_sdk_init()

add_subdirectory(src/hello)
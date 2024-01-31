cmake_minimum_required(VERSION 3.22)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(FetchContent)

project(hello-pico-ros)

pico_sdk_init()

message("Fetching micro_ros repository...")
FetchContent_Declare(
  micro_ros
  GIT_REPOSITORY git@github.com:micro-ROS/micro_ros_raspberrypi_pico_sdk.git
  GIT_TAG        humble
)
FetchContent_MakeAvailable(micro_ros)

link_directories(${micro_ros_SOURCE_DIR}/libmicroros)

#TODO:DS: Should I bother adding the subdirectory?
add_subdirectory(src/hello)
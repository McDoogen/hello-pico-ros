#TODO:DS: Should I just fetch pico-sdk as well? Since I am fetching micro-ros.... ?

cmake_minimum_required(VERSION 3.22)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(FetchContent)

project(hello-pico-ros C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

#TODO:DS: Can I add an 'IF' so we only log this if it is not available?
message("Fetching micro_ros repository...")
FetchContent_Declare(
  micro_ros
  GIT_REPOSITORY git@github.com:micro-ROS/micro_ros_raspberrypi_pico_sdk.git
  GIT_TAG        humble
)
FetchContent_MakeAvailable(micro_ros)

link_directories(${micro_ros_SOURCE_DIR}/libmicroros)

add_subdirectory(src/hello)
add_subdirectory(src/potentiometer_reader)
add_subdirectory(src/servo_spinner)
add_executable(hello
    hello.cpp
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(hello pico_stdlib microros)
target_include_directories(hello PUBLIC ${CMAKE_SOURCE_DIR}/lib/micro-ros/libmicroros/include)

# Do I need these?
SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")

# Configure Pico
pico_enable_stdio_usb(hello 1)
pico_enable_stdio_uart(hello 0)
add_compile_definitions(PICO_UART_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_DEFAULT_CRLF=0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hello)
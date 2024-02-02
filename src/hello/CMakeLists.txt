add_executable(hello
    hello.cpp
    pico_uart_transport.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(hello pico_stdlib microros)   #TODO:DS: What is microros here?
target_include_directories(hello PUBLIC ${micro_ros_SOURCE_DIR}/libmicroros/include)

# Configure Pico
pico_enable_stdio_usb(hello 1)
pico_enable_stdio_uart(hello 0)
add_compile_definitions(PICO_UART_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_DEFAULT_CRLF=0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hello)
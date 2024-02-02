add_executable(potentiometer_reader
    potentiometer_reader.cpp
    pico_uart_transport.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(potentiometer_reader pico_stdlib hardware_adc microros)
target_include_directories(potentiometer_reader PUBLIC ${micro_ros_SOURCE_DIR}/libmicroros/include)

# Configure Pico
pico_enable_stdio_usb(potentiometer_reader 1)
pico_enable_stdio_uart(potentiometer_reader 0)
add_compile_definitions(PICO_UART_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_DEFAULT_CRLF=0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(potentiometer_reader)
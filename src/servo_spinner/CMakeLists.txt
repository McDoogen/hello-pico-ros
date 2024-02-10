add_executable(servo_spinner
    servo_spinner.cpp
    pico_uart_transport.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(servo_spinner pico_stdlib hardware_adc hardware_pwm microros)
target_include_directories(servo_spinner PUBLIC ${micro_ros_SOURCE_DIR}/libmicroros/include)

# Configure Pico
pico_enable_stdio_usb(servo_spinner 1)
pico_enable_stdio_uart(servo_spinner 0)
add_compile_definitions(PICO_UART_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_DEFAULT_CRLF=0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(servo_spinner)
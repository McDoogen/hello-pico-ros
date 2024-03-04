#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/int32.h>
#include <rmw_microros/rmw_microros.h>

extern "C"
{
    #include "pico_uart_transport.h"
}

// rcl_publisher_t publisher;
rcl_subscription_t subscriber;
std_msgs__msg__Int32 msg;

const uint SERVO1_PIN = 14;
const uint LED_PIN = PICO_DEFAULT_LED_PIN;
const float LOWER_PULSE = 0.5;
const float UPPER_PULSE = 2.5;

void subscription_callback(const void * msgin)
{
    //TODO:DS: How can I get a log of what is being displayed? Should I just publish it back?
    //TODO:DS: 0 - 4095 uint32?
    //TODO:DS: Move this documentation to the servo_spinner.md
    //TODO:DS: Let's move this all into a library to use for RC motor control
    // scale 0-4095 to 0.5 to 1.0
    //0.00012 + 0.5
    // now, what is msgin?
    /* RC Servo Information
        Wire Colors
            Brown : GND
            Red : VCC
            Orange : CTRL
        
        Typical Pulse Calculation (source: https://en.wikipedia.org/wiki/Servo_control)
            These ranges can vary, but this is the basic concept
            20ms period for each pulse
            1.0 ms at VCC and remaining 19.0ms at 0V for -90 deg
            1.5 ms at VCC and remaining 18.5ms at 0V for 0 deg
            2.0 ms at VCC and remaining 18.0ms at 0V for 90 deg

        Pi Pico PWM Period Preparation (Source: Pi Pico Datasheet Section 4.5 - https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
            This step sets up the PWM to operate at 20ms period
            Default RP2040 Clock Speed: 125 MHz
            period = ( TOP + 1 ) x (CSR_PH_CORRECT + 1) x ( DIV_INT + DIV_FRAC/16 ) [Source: 4.5.2.6]
            TOP (0 - 65536)         = 65465     -> pwm_set_wrap(SERVO1_SLICE_NUM,65465);
            CSR_PH_CORRECT (0 - 1)  = 0         -> 
            DIV_INT (1.f - 256.f)   = 38
            DIV_FRAC                = 3
            DIV                     = 38.1875f  -> pwm_set_clkdiv(SERVO1_SLICE_NUM, 38.1875f);

        Pi Pico PWM Channel Level
            This step sets up the PWM pulse that sets the RC Servo position
            -90 : pwm_set_gpio_level(SERVO1_PIN, 65465 / (20 / 1.0f) );
            0   : pwm_set_gpio_level(SERVO1_PIN, 65465 / (20 / 1.5f) );
            90  : pwm_set_gpio_level(SERVO1_PIN, 65465 / (20 / 2.0f) );
            ^ Double check that this is all correct :D


    */
    std_msgs__msg__Int32* msg = (std_msgs__msg__Int32*) msgin;
    
    float pulse = (msg->data * 0.00012) + 0.5;
    
    //TODO:DS: Test out setting pulse to something like 0.5 to test
    //TODO:DS: Ok! It's working! :D Let's change this to send the angle over a twist type message instead of just an int32
    //TODO:DS: Also we need to come back and clean up these documents now :)

    uint angle_1 = 65465 / (20 / pulse);
    // uint angle_1 = 65465 / (20 / 1.0f);
    pwm_set_gpio_level(SERVO1_PIN, angle_1);
}

int main()
{
    rmw_uros_set_custom_transport(
		true,
		NULL,
		pico_serial_transport_open,
		pico_serial_transport_close,
		pico_serial_transport_write,
		pico_serial_transport_read
	);

    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    rcl_timer_t timer;
    rcl_node_t node;
    rcl_allocator_t allocator;
    rclc_support_t support;
    rclc_executor_t executor;

    allocator = rcl_get_default_allocator();

    // Wait for agent successful ping for 2 minutes.
    const int timeout_ms = 1000; 
    const uint8_t attempts = 120;

    rcl_ret_t ret = rmw_uros_ping_agent(timeout_ms, attempts);

    if (ret != RCL_RET_OK)
    {
        // Unreachable agent, exiting program.
        return ret;
    }

    rclc_support_init(&support, 0, NULL, &allocator);

    rclc_node_init_default(&node, "pico_node", "", &support);
    rclc_subscription_init_default(
        &subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "pico_subscriber");


    rclc_executor_init(&executor, &support.context, 1, &allocator);
    rclc_executor_add_subscription(&executor, &subscriber, &msg, subscription_callback, ON_NEW_DATA);

    // Turn on the LED
    gpio_put(LED_PIN, 1);

    // Setup Servo
    gpio_set_function(SERVO1_PIN, GPIO_FUNC_PWM);
    const uint SERVO1_SLICE_NUM = pwm_gpio_to_slice_num(SERVO1_PIN);
    pwm_set_phase_correct(SERVO1_SLICE_NUM, false);
    pwm_set_clkdiv(SERVO1_SLICE_NUM, 38.1875f);
    pwm_set_wrap(SERVO1_SLICE_NUM,65465);
    pwm_set_enabled(SERVO1_SLICE_NUM, true);

    //TODO:DS: Test, set to lowest angle
    uint angle_1 = 65465 / (20 / 1.0f);
    pwm_set_gpio_level(SERVO1_PIN, angle_1);


    msg.data = 0;
    while (true)
    {
                rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));

    }
    return 0;
}
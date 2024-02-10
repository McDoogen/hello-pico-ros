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

void subscription_callback(const void * msgin)
{
    //TODO:DS: How can I get a log of what is being displayed? Should I just publish it back?
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

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    const uint SERVO1_PIN = 14;

    stdio_init_all();
    adc_init();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    adc_gpio_init(26);
    adc_select_input(0);


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


    msg.data = 0;
    while (true)
    {
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
    }
    return 0;
}
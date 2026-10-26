
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_LED0 1000
#define SLEEP_TIME_LED1 350
#define BLINK_DURATION 150

#define STACK_SIZE 512
#define THREAD_PRIORITY 7

// Define os LEDs usando Device Tree
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

// Verifica se os LEDs estão definidos no Device Tree
#if DT_NODE_HAS_STATUS(LED0_NODE, okay) && DT_NODE_HAS_STATUS(LED1_NODE, okay)
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
#else
#error "Unsupported board: LED aliases not defined"
#endif

// Thread responsável pelo LED0 (1000 ms)
void led0_thread(void)
{
    gpio_pin_set_dt(&led0, 0);
    while (1) {
        gpio_pin_toggle_dt(&led0);
        k_msleep(BLINK_DURATION);

        gpio_pin_toggle_dt(&led0);
        k_msleep(SLEEP_TIME_LED0 - BLINK_DURATION);
    }
}

// Thread responsável pelo LED1 (500 ms)
void led1_thread(void)
{   
    gpio_pin_set_dt(&led1, 0);
    while (1) {
        gpio_pin_toggle_dt(&led1);
        k_msleep(BLINK_DURATION);

        gpio_pin_toggle_dt(&led1);
        k_msleep(SLEEP_TIME_LED1 - BLINK_DURATION);
    }
}

// Criação das duas threads
K_THREAD_DEFINE(led0_thread_id, STACK_SIZE, led0_thread,
                NULL, NULL, NULL, THREAD_PRIORITY, 0, 0);

K_THREAD_DEFINE(led1_thread_id, STACK_SIZE, led1_thread,
                NULL, NULL, NULL, THREAD_PRIORITY, 0, 0);

int main(void)
{
    int ret;

    // Verifica se os dispositivos estão prontos
    if (!gpio_is_ready_dt(&led0) || !gpio_is_ready_dt(&led1)) {
        printk("Error: LED device not ready\n");
        return;
    }

    // Configura LED0 como saída
    ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error configuring LED0\n");
        return;
    }

    // Configura LED1 como saída
    ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error configuring LED1\n");
        return;
    }

    printk("LED0: 1000 ms | LED1: 500 ms\n");
}

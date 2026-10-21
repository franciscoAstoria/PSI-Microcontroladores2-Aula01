#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

// Define o LED usando Device Tree
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

// Verifica se os LEDs está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
#else
#error "Unsupported board: led1 devicetree alias is not defined"
#endif

void blink_led_demo() {
    printk("[%lld ms] Piscando LED (500ms)!\n", k_uptime_get());
    gpio_pin_toggle_dt(&led0);
    printk("[%lld ms] Piscando LED (1000ms)!\n", k_uptime_get());
    gpio_pin_toggle_dt(&led1);
    k_msleep(500);
    printk("[%lld ms] Piscando LED (500ms)!\n", k_uptime_get());
    gpio_pin_toggle_dt(&led0);
    k_msleep(500);
}

void blink_led_desafio() {
    for (int i = 0; i < 140; i++) {
        if (i % 7 == 0) {
            printk("[%lld ms] Piscando LED (350ms)!\n", k_uptime_get());
            gpio_pin_toggle_dt(&led0);
        }
        if (i % 20 == 0) {
            printk("[%lld ms] Piscando LED (1000ms)!\n", k_uptime_get());
            gpio_pin_toggle_dt(&led1);
        } 
        k_msleep(50);
    }
}


void main(void)
{
    int ret;

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&led0)) {
        printk("Error: LED device %s is not ready\n", led0.port->name);
        return;
    }

    if (!gpio_is_ready_dt(&led1)) {
        printk("Error: LED device %s is not ready\n", led1.port->name);
        return;
    }

    // Configura o pino como saída
    ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }

    ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }

    while (1) {
        // blink_led_demo();
        blink_led_desafio();
    }
}
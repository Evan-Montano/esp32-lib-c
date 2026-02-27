#include "gpio.h"

int set_gpio_out(int pin, int high) {
    if (pin < 0 || pin > 31) return -1;
    if (high == 1) {
        setBitHigh(&GPIO_OUT_REG, pin);
        // GPIO_OUT_REG |= (1 << pin);
        return 1;
    }
    else if (high == 0) {
        GPIO_OUT_REG = GPIO_OUT_REG & ~(1 << pin);
        return 0;
    }
    return -1;
}//end set_gpio_out

int toggle_gpio_out(int pin) {
    if (pin < 0 || pin > 31) return -1;
    GPIO_OUT_REG ^= (1 << pin);
    return 0;
}//end toggle_gpio_out

int conf_gpio_simple_out(int pin) {
    
}//end conf_gpio_simple_out
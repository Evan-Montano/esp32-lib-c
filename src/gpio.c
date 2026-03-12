#include "gpio.h"

bool gpio_setOutState(uint8_t pin, bool state) {
    if ((pin < 20)
        || (pin > 20 && pin < 24)
        || (pin > 24 && pin < 28)
        || (pin > 31 && pin < 34)) {
        u_setBit32(GPIO_OUT_REG, pin, state);
        return u_getBitValue32(GPIO_OUT_REG, pin) == state;
    }
    return false;
}//end set_gpio_out

bool gpio_toggleOutState(uint8_t pin) {
    if ((pin < 20)
        || (pin > 20 && pin < 24)
        || (pin > 24 && pin < 28)
        || (pin > 31 && pin < 34)) {
        bool val = u_getBitValue32(GPIO_OUT_REG, pin);
        u_toggleBit32(GPIO_OUT_REG, pin);
        return val != u_getBitValue32(GPIO_OUT_REG, pin);
    }
    return false;
}

// NOTE: Only the following GPIOs can be configured for input:
// (0-19, 21-23, 25-27, 32-39)
bool gpio_getInState(uint8_t pin) {
    if ((pin < 20)
        || (pin > 20 && pin < 24)
        || (pin > 24 && pin < 28)
        || (pin > 31 && pin < 40)) {
        return u_getBitValue32(GPIO_IN_REG, pin);
    }
    return false;
}

bool gpio_configAsSimpleOutput(uint8_t pin) {
    if ((pin < 20)
        || (pin > 20 && pin < 24)
        || (pin > 24 && pin < 28)
        || (pin > 31 && pin < 34)) {
            
        u_setBitRange32(IO_MUX_GPIO_REG(pin), 12, WIDTH_MASK(3), 2);
        u_setBitRange32(GPIO_FUNC_OUT_SEL_CFG_REG(pin), 0, WIDTH_MASK(9), 256);
        u_setBit32(GPIO_FUNC_OUT_SEL_CFG_REG(pin), GPIO_FUNC_OEN_INV_SEL, 0);
        u_setBit32(GPIO_FUNC_OUT_SEL_CFG_REG(pin), GPIO_FUNC_OEN_SEL, 1);
        u_setBit32(GPIO_FUNC_OUT_SEL_CFG_REG(pin), GPIO_FUNC_OUT_INV_SEL, 0);
        u_setBit32(GPIO_ENABLE_REG, pin, 1);
        return true;
    }
    return false;
}

// NOTE: Only the following GPIOs can be configured for input:
// (0-19, 21-23, 25-27, 32-39)
bool gpio_configAsSimpleInput(uint8_t pin) {
    if ((pin < 20)
        || (pin > 20 && pin < 24)
        || (pin > 24 && pin < 28)
        || (pin > 31 && pin < 40)) {
        u_setBit32(IO_MUX_GPIO_REG(pin), FUN_IE, 1);
        u_setBit32(GPIO_ENABLE_REG, pin, 0);
        return true;
    }
    return false;
}
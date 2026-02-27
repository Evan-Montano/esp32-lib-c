#include "gpio.h"

// FIXME GPIOs 32-39 can be set
bool gpio_setState(uint8_t pin, bool state) {
    if (pin < 32) {
        u_setBit32(GPIO_OUT_REG, pin, state);
        return u_getBitValue32(GPIO_OUT_REG, pin) == state;
    }
    return false;
}//end set_gpio_out

// FIXME GPIOs 32-39 can be set
bool gpio_toggleState(uint8_t pin) {
    if (pin < 32) {
        bool val = u_getBitValue32(GPIO_OUT_REG, pin);
        u_toggleBit32(GPIO_OUT_REG, pin);
        return val != u_getBitValue32(GPIO_OUT_REG, pin);
    }
    return false;
}

// NOTE: Only the following GPIOs can be configured for output:
// (0-19, 21-23, 25-27, 32-33)
bool gpio_configAsSimpleOutput(uint8_t pin) {
    if ((pin < 20)
        || (pin > 20 && pin < 24)
        || (pin > 24 && pin < 28)
        || (pin > 31 && pin < 34)) {
        u_setBitRange32(GPIO_FUNC_OUT_SEL_CFG_REG(pin), GPIO_FUNC_OUT_SEL, 9, 0x100);
        u_setBit32(GPIO_FUNC_OUT_SEL_CFG_REG(pin), GPIO_FUNC_OEN_INV_SEL, 0);
        u_setBit32(GPIO_FUNC_OUT_SEL_CFG_REG(pin), GPIO_FUNC_OEN_SEL, 1);
        u_setBit32(GPIO_FUNC_OUT_SEL_CFG_REG(pin), GPIO_FUNC_OUT_INV_SEL, 0);
        return true;
    }
    return false;
}
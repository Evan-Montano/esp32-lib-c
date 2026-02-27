#ifndef GPIO_H
#define GPIO_H

// ========== Include Statements ========== //
#include "bin_util.h"


// ========== Definitions ========== //
#define GPIO(n) (n)

// ========== Memory-Mapped Register Definitions ========== //

// This macro represents the memory-mapped gpio output register.
// Reading/writing this register accesses the GPIO output state.
// Bit n corresponds to GPIO pin n (0–31).
#define GPIO_OUT_REG ((reg32_t)(uintptr_t)0x3FF44004)

// This macro represents the memory-mapped gpio enable register.
// Writing to this register controls the I/O properties of gpio use.
// 0:input      1:output
#define GPIO_ENABLE_REG ((reg32_t)(uintptr_t)0x3FF44020)

// Peripheral output selection for GPIO (PIN)
// Writing to this register controls the configuration of this GPIO
#define GPIO_FUNC_OUT_SEL_CFG_REG(PIN) ((reg32_t)(uintptr_t)(0x3FF44530 + (uint32_t)PIN))

// Property of GPIO_FUNC_OUT_SEL_CFG_REG
// 1: Invert the output enable signal (R/W)
// 0: do not invert the output enable signal (R/W)
#define GPIO_FUNC_OEN_INV_SEL 11

// Property of GPIO_FUNC_OUT_SEL_CFG_REG
// 1: Force the output enable signal to be sourced from bit n of GPIO_ENABLE_REG
// 0: Use output enable signal from peripheral. (R/W)
#define GPIO_FUNC_OEN_SEL 10

// Property of GPIO_FUNC_OUT_SEL_CFG_REG
// 1: Invert the output value; 0: do not invert the output value. (R/W)
#define GPIO_FUNC_OUT_INV_SEL 9

// Property of GPIO_FUNC_OUT_SEL_CFG_REG
// Selection control for GPIO output n. A value of s (0<=s<256)
// connects peripheral output s to GPIO output n. A value of 256 (0x100) selects bit n of
// GPIO_OUT_REG/GPIO_OUT1_REG and GPIO_ENABLE_REG/GPIO_ENABLE1_REG as the output
// value and output enable. (R/W)
#define GPIO_FUNC_OUT_SEL 0


// ========== Method Declarations ========== //
// NOTE: all methods are prefixed with 'gpio', for clarity of the function's origin.

// Sets the specified state (t:HIGH/f:LOW) of the specified GPIO (pin)
bool gpio_setState(uint8_t pin, bool state);

// Toggles the state (HIGH/LOW) of the specified GPIO (pin)
bool gpio_toggleState(uint8_t pin);

// Configures a gpio pin as simple output.
// To configure a pin as simple GPIO output, the GPIO Matrix GPIO_FUNCx_OUT_SEL register 
// is configured with a special peripheral index value 256 (0x100).
// NOTE: Only the following GPIOs can be configured for output: (0-19, 21-23, 25-27, 32-33)
bool gpio_configAsSimpleOutput(uint8_t pin);

#endif
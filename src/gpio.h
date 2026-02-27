#ifndef GPIO_H
#define GPIO_H

// ========== Include Statements ========== //
#include "bin_util.h"

// ========== Definitions ========== //

// This macro represents the memory-mapped gpio output register.
// Reading/writing this register accesses the GPIO output state.
// Bit n corresponds to GPIO pin n (0–31).
#define GPIO_OUT_REG *((reg32_t) 0x3FF44004)

// This macro represents the memory-mapped gpio enable register.
// Writing to this register controls the I/O properties of non-simple gpio use.
// 0:input      1:output
// This is for NON-SIMPLE gpio output.
#define GPIO_ENABLE_REG *((reg32_t) 0x3FF44020)

// DOCME
#define GPIO_FUNC_OUT_SEL_CFG_REG(PIN) *((reg32_t) (0x3FF44530 + (uint32_t)PIN))

// ========== Method Declarations ========== //

// DOCME
int set_gpio_out(int pin, int high);

// DOCME
int toggle_gpio_out(int pin);

// Configures a gpio pin as simple output.
int conf_gpio_simple_out(int pin);

#endif
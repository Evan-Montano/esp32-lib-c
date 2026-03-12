#ifndef GPIO_H
#define GPIO_H

// ========== Include Statements ========== //
#include "bin_util.h"

// ========== Memory-Mapped Register Definitions ========== //

// This macro represents the memory-mapped gpio output register.
// Reading/writing this register accesses the GPIO output state.
// Bit n corresponds to GPIO pin n (0–31).
#define GPIO_OUT_REG ((reg32_t)0x3FF44004)

// DOCME
#define GPIO_IN_REG ((reg32_t)0x3FF4403C)

// This macro represents the memory-mapped gpio enable register.
// Writing to this register controls the I/O properties of gpio use.
// 0:input      1:output
#define GPIO_ENABLE_REG ((reg32_t)0x3FF44020)

// Peripheral output selection for GPIO (PIN)
// Writing to this register controls the configuration of this GPIO
#define GPIO_FUNC_OUT_SEL_CFG_REG(PIN) ((reg32_t)(0x3FF44530 + (PIN * 4)))

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
//end GPIO_FUNC_OUT_SEL_CFG_REG

// DOCME
static const uintptr_t io_mux_table[] = {
    [0] = 0x3FF49044,
    [1] = 0x3FF49088,
    [2] = 0x3FF49040,
    [3] = 0x3FF49084,
    [4] = 0x3FF49048,
    [5] = 0x3FF4906C,
    [6] = 0x3FF49060,
    [7] = 0x3FF49064,
    [8] = 0x3FF49068,
    [9] = 0x3FF49054,
    [10] = 0x3FF49058,
    [11] = 0x3FF4905C,
    [12] = 0x3FF49034,
    [13] = 0x3FF49038,
    [14] = 0x3FF49030,
    [15] = 0x3FF4903C,
    [16] = 0x3FF4904C,
    [17] = 0x3FF49050,
    [18] = 0x3FF49070,
    [19] = 0x3FF49074,
    [20] = 0x3FF49078,
    [21] = 0x3FF4907C,
    [22] = 0x3FF49080,
    [23] = 0x3FF4908C,
    [25] = 0x3FF49024,
    [26] = 0x3FF49028,
    [27] = 0x3FF4902C,
    [32] = 0x3FF4901C,
    [33] = 0x3FF49020,
    [34] = 0x3FF49014,
    [35] = 0x3FF49018,
    [36] = 0x3FF49004,
    [37] = 0x3FF49008,
    [38] = 0x3FF4900C,
    [39] = 0x3FF49010
};

// Input enable of the pin. 1: input enabled; 0: input disabled. (R/W)
#define FUN_IE 9

// Uses the static io_mux_table array to get the appropriate
// IO_MUX_x_REG register on hardware
#define IO_MUX_GPIO_REG(PIN) ((reg32_t)io_mux_table[(PIN)])

// ========== Method Declarations ========== //
// NOTE: all methods are prefixed with 'gpio', for clarity of the function's origin.

// Sets the specified state (t:HIGH/f:LOW) of the specified GPIO (pin)
// NOTE: Only the following GPIOs can be configured for output:
// (0-19, 21-23, 25-27, 32-33)
bool gpio_setOutState(uint8_t pin, bool state);

// Toggles the state (HIGH/LOW) of the specified GPIO (pin)
// NOTE: Only the following GPIOs can be configured for output:
// (0-19, 21-23, 25-27, 32-33)
bool gpio_toggleOutState(uint8_t pin);

// Gets the state (t:HIGH/f:LOW) of the specified GPIO (pin)
// NOTE: Only the following GPIOs can be configured for input:
// (0-19, 21-23, 25-27, 32-39)
bool gpio_getInState(uint8_t pin);

// Configures a gpio pin as simple output.
// To configure a pin as simple GPIO output, the GPIO Matrix GPIO_FUNCx_OUT_SEL register 
// is configured with a special peripheral index value 256 (0x100).
// NOTE: Only the following GPIOs can be configured for output: (0-19, 21-23, 25-27, 32-33)
bool gpio_configAsSimpleOutput(uint8_t pin);

// Configures a gpio pin as simple input.
// The GPIO_IN_REG/GPIO_IN1_REG register holds the input values of each GPIO pin.
// The input value of any GPIO pin can be read at any time without configuring the GPIO Matrix for a particular
// peripheral signal. However, it is necessary to enable the input in the IO MUX by setting the FUN_IE bit in the
// IO_MUX_x_REG register corresponding to pin X
bool gpio_configAsSimpleInput(uint8_t pin);

#endif
#ifndef ESP_TIMER_H
#define ESP_TIMER_H

// ========== Include Statements ========== //
#include "bin_util.h"

// ========== Memory-Mapped Register Definitions ========== //

// Timer 0/1 configuration and control registers
    // Timer 0/1 configuration register
    #define TIMG_T0CONFIG_REG(N) ((reg32_t)((N) == 0 ? 0x3FF5F000 : 0x3FF60000))
        // When set, the timer x time-base counter is enabled
        #define TIMG_T_EN 31

        // When set, the timer x time-base counter will increment every clock tick.
        // When cleared, the timer x time-base counter will decrement. (R/W)
        #define TIMG_T_INCREASE 30

        // When set, timer x auto-reload at alarm is enabled. (R/W)
        #define TIMG_T_AUTORELOAD 29

        // Timer x clock (Tx_clk) prescale value. (R/W)
        #define TIMG_T_DIVIDER 13

        // When set, an alarm will generate an edge type interrupt. (R/W)
        #define TIMG_T_EDGE_INT_EN 12

        // When set, an alarm will generate a level type interrupt. (R/W)
        #define TIMG_T_LEVEL_INT_EN

        // When set, the alarm is enabled. This bit is automatically cleared once an alarm occurs. (R/W)
        #define TIMG_T_ALARM_EN 10

    // Timer 0/1 current value, low 32 bits
    #define TIMG_T0LO_REG(N) ((reg32_t)((N) == 0 ? 0x3FF5F004 : 0x3FF60004))

    // Timer 0/1 current value, high 32 bits
    #define TIMG_T0HI_REG(N) ((reg32_t)((N) == 0 ? 0x3FF5F008 : 0x3FF60008))

    // Write to copy current timer value to TIMGn_T0_(LO/HI)_REG
    #define TIMG_T0UPDATE_REG(N) ((reg32_t)((N) == 0 ? 0x3FF5F00C : 0x3FF6000C))

    // Timer 0/1 alarm value, low 32 bits
    #define TIMG_T0ALARMLO_REG(N) ((reg32_t)((N) == 0 ? 0x3FF5F010 : 0x3FF60010))

    // Timer 0/1 alarm value, high bits
    #define TIMG_T0ALARMHI_REG(N) ((reg32_t)((N) == 0 ? 0x3FF5F014 : 0x3FF60014))

    // Timer 0/1 reload value, low 32 bits
    #define TIMG_T0LOADLO_REG(N) ((reg32_t)((N) == 0 ? 0x3FF5F018 : 0x3FF60018))

    // Timer 0/1 reload value, high 32 bits
    #define TIMG_T0LOADHI_REG(N) ((reg32_t)((N) == 0 ? 0x3FF5F01C : 0x3FF6001C))

    // Write to reload timer from TIMGn_T0_(LOADLOLOADHI)_REG
    #define TIMG_T0LOAD_REG(N) ((reg32_t)((N) == 0 ? 0x3FF5F020 : 0x3FF60020))
//end

// ========== Method Declarations ========== //

// Starts the 64-bit time-base counter from the current value
// timer: vals(0,1,2,3)
// ctDown: 0:Count up 1:Count Down
void timg_begin(uint8_t timer, bool ctDwn);

// The following methods are variations to get the value of the specified timer
// timer: vals(0,1,2,3)
uint32_t timg_stop32_lo(uint8_t timer);
uint32_t timg_stop32_hi(uint8_t timer);
uint64_t timg_stop64(uint8_t timer);

// Resets the specified timer to a value of 0
// timer: vals(0,1,2,3)
void timg_reset(uint8_t timer);

#endif
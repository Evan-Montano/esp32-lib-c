#include "timer.h"

// Counting can be enabled and disabled by setting and clearing TIMGn_Tx_EN.
void timg_begin(uint8_t timer, bool ctDwn) {
    reg32_t timConfigRef;
    
    // set the timer reference
    switch (timer) {
        case 0:
            timConfigRef = TIMG_T0CONFIG_REG(0);
            break;
        case 1:
            timConfigRef = TIMG_T0CONFIG_REG(1);
            break;
        case 2:
            break;
        case 3:
            break;
        default:
        break;
    }

    // Set count up or down
    u_setBit32(timConfigRef, TIMG_T_INCREASE, !ctDwn);
    // Start timer 0:0
    u_setBit32(timConfigRef, TIMG_T_EN, 1);
}

// Counting can be enabled and disabled by setting and clearing TIMGn_Tx_EN.
uint32_t timg_stop32_lo(uint8_t timer) {
    reg32_t timConfigRef;
    reg32_t timLoRef;
    
    // set the timer reference
    switch (timer) {
        case 0:
            timConfigRef = TIMG_T0CONFIG_REG(0);
            timLoRef = TIMG_T0LO_REG(0);
            break;
        case 1:
            timConfigRef = TIMG_T0CONFIG_REG(1);
            timLoRef = TIMG_T0LO_REG(0);
            break;
        case 2:
            break;
        case 3:
            break;
        default:
        break;
    }

    // Disable counting
    u_setBit32(timConfigRef, TIMG_T_EN, 0);

    // Get and return the current value in TIMG_T0LO_REG(N)
    return (uint32_t)*timLoRef;
}

// Counting can be enabled and disabled by setting and clearing TIMGn_Tx_EN.
uint32_t timg_stop32_hi(uint8_t timer) {
    reg32_t timConfigRef;
    reg32_t timHiRef;
    
    // set the timer reference
    switch (timer) {
        case 0:
            timConfigRef = TIMG_T0CONFIG_REG(0);
            timHiRef = TIMG_T0HI_REG(0);
            break;
        case 1:
            timConfigRef = TIMG_T0CONFIG_REG(1);
            timHiRef = TIMG_T0HI_REG(0);
            break;
        case 2:
            break;
        case 3:
            break;
        default:
        break;
    }

    // Disable counting
    u_setBit32(timConfigRef, TIMG_T_EN, 0);

    // Get and return the current value in TIMG_T0LO_REG(N)
    return (uint32_t)*timHiRef;
}

uint64_t timg_stop64(uint8_t timer) {
    uint64_t hiVal = (uint64_t)timg_stop32_hi(timer);
    uint64_t loVal = (uint64_t)timg_stop32_lo(timer);
    return (hiVal & loVal);
}

void timg_reset(uint8_t timer) {
    reg32_t timReloadRef;
    
    // set the timer reference
    switch (timer) {
        case 0:
            timReloadRef = TIMG_T0LOAD_REG(0);
            break;
        case 1:
            timReloadRef = TIMG_T0LOAD_REG(1);
            break;
        case 2:
            break;
        case 3:
            break;
        default:
        break;
    }

    // First stop the timer
    timg_stop32_lo(timer);

    // Reload timer by setting any value to the register
    u_setBit32(timReloadRef, 0, 1);
}
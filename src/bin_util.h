#ifndef BIN_UTIL_H
#define BIN_UTIL_H

// ========== Imports ========== //
#include <stdint.h> // precise unsigned variables
#include <stdbool.h>

// ========== Definitions ========== //

// To be used for bit range setters as the "width" param.
#define WIDTH_MASK(n) ((n) == 32 ? 0xFFFFFFFFU : ((1U << (n)) - 1U))
#ifdef __cplusplus
extern "C" {
#endif

// ========== Methods ========== //
// NOTE: all methods are prefixed with 'u', standing for "utility", for clear distinction during implementation of the origin of the function

// Used to set a single chosen bit to either a high or low state.
// reg: direct value at address of register in memory-mapped hardware.
// bit: value of target bit position (31-0).
// state: value to set bit to (0:LOW 1:HIGH).
void u_setBit32(volatile uint32_t *reg, uint8_t bit, bool state);


// Used to set a chosen bit's value to the inverse of the existing value.
// reg: direct value at address of register in memory-mapped hardware.
// bit: value of target bit position (31-0).
void u_toggleBit32(volatile uint32_t *reg, uint8_t bit);


// Used to set an gap-less bit range to a desired value without affecting other bits. Existing values are first cleared out.
// reg: direct value at address of register in memory-mapped hardware.
// lsb_pos: position of the Lease Significant Bit in the desired range (31-0). Used for left-shifts.
// width: USE WIDTH_MASK(n) MACRO** left-to-right size of the desired range to alter.
// val: using binary interpretation as the expected value for the desired range.
void u_setBitRange32(volatile uint32_t *reg, uint8_t lsb_pos, uint32_t width_mask, uint32_t val);


// Used to get the binary value of a specified bit.
// reg: direct value at address of register in memory-mapped hardware.
// bit: value of target bit position (31-0).
bool u_getBitValue32(volatile uint32_t *reg, uint8_t bit);


// Used to get the value of a specified bit range.
// reg: direct value at address of register in memory-mapped hardware.
// lsb_pos: position of the Lease Significant Bit in the desired range (31-0). Used for left-shifts.
// width: USE Wx MACROS** left-to-right size of the desired range to read.
uint32_t u_getBitRangeValue32(volatile uint32_t *reg, uint8_t lsb_pos, uint32_t width_mask);

#ifdef __cplusplus
}
#endif

#endif
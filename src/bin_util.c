#include "bin_util.h"

// ========== Implementations ========== //
void u_setBit32(reg32_t reg, uint8_t bit, bool state) {
	if (bit < 32) {
		if (state == 1) {
			*reg |= (1 << bit);
		}
		else {
			*reg &= ~(1 << bit);
		}
	}
}

void u_toggleBit32(reg32_t reg, uint8_t bit) {
	if (bit < 32) {
		*reg ^= (1 << bit);
	}
}

void u_setBitRange32(reg32_t reg, uint8_t lsb_pos, uint32_t width_mask, uint32_t val) {
	if (lsb_pos < 32) {
		// We are assuming that the WIDTH_MASK(n) macro is utilized and that "val"s binary is correct.
		// This is up to the developer to ensure. 
		uint32_t mask = width_mask << lsb_pos;
		*reg = (*reg & ~mask) | ((val & width_mask) << lsb_pos);
	}
}

bool u_getBitValue32(reg32_t reg, uint8_t bit) {
    bool ret = false;
    if (bit < 32) {
        uint32_t mask = *reg & (1U << bit);
        ret = ((*reg & mask) >> bit);
    }
    return ret;
}

uint32_t u_getBitRangeValue32(reg32_t reg, uint8_t lsb_pos, uint32_t width_mask) {
    uint32_t ret = 0;
    if (lsb_pos < 32) {
        uint32_t mask = *reg & (width_mask << lsb_pos);
        ret = (*reg & mask) >> lsb_pos;
    }
    return ret;
}
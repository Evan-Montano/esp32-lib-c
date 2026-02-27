#include "../src/bin_util.h"
#include "test.h"

void test_u_setBit32(void) {
    ptest();

    uint32_t n;
    volatile uint32_t *n_ptr;
    uint32_t expected;

    // ----------------------------
    // Basic set operations
    // ----------------------------
    n = 0B0010000100011010;
    n_ptr = &n;

    expected = 0B0010000100011011;
    u_setBit32(n_ptr, 0, 1);
    passert(n == expected);

    expected = 0B0010000101011011;
    u_setBit32(n_ptr, 6, 1);
    passert(n == expected);

    // ----------------------------
    // Setting a bit that is already 1
    // should NOT change value
    // ----------------------------
    expected = n;
    u_setBit32(n_ptr, 6, 1);
    passert(n == expected);

    // ----------------------------
    // Clear bit tests (value = 0)
    // ----------------------------
    expected = 0B0010000100011011;
    u_setBit32(n_ptr, 6, 0);
    passert(n == expected);

    expected = 0B0010000100011010;
    u_setBit32(n_ptr, 0, 0);
    passert(n == expected);

    // ----------------------------
    // Edge cases: LSB and MSB
    // ----------------------------
    n = 0;
    n_ptr = &n;

    expected = 1U;
    u_setBit32(n_ptr, 0, 1);
    passert(n == expected);

    expected = (1U << 31) | 1U;
    u_setBit32(n_ptr, 31, 1);
    passert(n == expected);

    // Clear MSB
    expected = 1U;
    u_setBit32(n_ptr, 31, 0);
    passert(n == expected);

    // ----------------------------
    // Full-word behavior
    // ----------------------------
    n = 0xFFFFFFFF;
    n_ptr = &n;

    expected = 0xFFFFFFFF;
    u_setBit32(n_ptr, 10, 1);
    passert(n == expected);

    expected = 0xFFFFFBFF; // bit 10 cleared
    u_setBit32(n_ptr, 10, 0);
    passert(n == expected);
}

void test_u_toggleBit32(void) {
    ptest();

    uint32_t n;
    volatile uint32_t *n_ptr;
    uint32_t expected;

    // --------------------------------
    // Basic toggle: 0 -> 1
    // --------------------------------
    n = 0B0010000100011010;
    n_ptr = &n;

    expected = 0B0010000100011011;
    u_toggleBit32(n_ptr, 0);
    passert(n == expected);

    // --------------------------------
    // Basic toggle: 1 -> 0
    // --------------------------------
    expected = 0B0010000100011010;
    u_toggleBit32(n_ptr, 0);
    passert(n == expected);

    // --------------------------------
    // Toggle middle bit
    // --------------------------------
    expected = 0B0010000101011010;
    u_toggleBit32(n_ptr, 6);
    passert(n == expected);

    // Toggle back (idempotency pair)
    expected = 0B0010000100011010;
    u_toggleBit32(n_ptr, 6);
    passert(n == expected);

    // --------------------------------
    // Edge cases: LSB and MSB
    // --------------------------------
    n = 0;
    n_ptr = &n;

    expected = 1U;
    u_toggleBit32(n_ptr, 0);
    passert(n == expected);

    expected = (1U << 31) | 1U;
    u_toggleBit32(n_ptr, 31);
    passert(n == expected);

    // Toggle MSB back off
    expected = 1U;
    u_toggleBit32(n_ptr, 31);
    passert(n == expected);

    // --------------------------------
    // Full word behavior
    // --------------------------------
    n = 0xFFFFFFFF;
    n_ptr = &n;

    expected = 0xFFFFFBFF; // bit 10 cleared
    u_toggleBit32(n_ptr, 10);
    passert(n == expected);

    expected = 0xFFFFFFFF; // toggle back
    u_toggleBit32(n_ptr, 10);
    passert(n == expected);
}

void test_u_setBitRange32(void) {
    ptest();

    uint32_t n;
    volatile uint32_t *n_ptr;
    uint32_t expected;

    // --------------------------------
    // Basic insertion into middle
    // --------------------------------
    n = 0xFFFFFFFF;
    n_ptr = &n;

    // Clear 4 bits at pos 8 and set to 0b1010
    expected = 0xFFFFFAFF; // bits 11-8 = 1010
    u_setBitRange32(n_ptr, 8, WIDTH_MASK(4), 0b1010);
    passert(n == expected);

    // --------------------------------
    // Range should clear existing bits first
    // --------------------------------
    n = 0x0000FF00;
    n_ptr = &n;

    expected = 0x00005500;
    u_setBitRange32(n_ptr, 8, WIDTH_MASK(8), 0x55);
    passert(n == expected);

    // --------------------------------
    // Value larger than width should be masked
    // --------------------------------
    n = 0;
    n_ptr = &n;

    expected = 0b011; // only lowest 3 bits kept
    u_setBitRange32(n_ptr, 0, WIDTH_MASK(3), 0b111011);
    passert(n == expected);

    // --------------------------------
    // LSB boundary (position 0)
    // --------------------------------
    n = 0xAAAAAAAA;
    n_ptr = &n;

    expected = (0xAAAAAAAA & ~WIDTH_MASK(5)) | 0b10101;
    u_setBitRange32(n_ptr, 0, WIDTH_MASK(5), 0b10101);
    passert(n == expected);

    // --------------------------------
    // MSB boundary (touching bit 31)
    // --------------------------------
    n = 0;
    n_ptr = &n;

    expected = (0b101 << 29);
    u_setBitRange32(n_ptr, 29, WIDTH_MASK(3), 0b101);
    passert(n == expected);

    // --------------------------------
    // Full 32-bit overwrite
    // --------------------------------
    n = 0xFFFFFFFF;
    n_ptr = &n;

    expected = 0x12345678;
    u_setBitRange32(n_ptr, 0, WIDTH_MASK(32), 0x12345678);
    passert(n == expected);

    // --------------------------------
    // Should not affect surrounding bits
    // --------------------------------
    n = 0xF000000F;
    n_ptr = &n;

    expected = 0xF000AA0F;
    u_setBitRange32(n_ptr, 8, WIDTH_MASK(8), 0xAA);
    passert(n == expected);

    // --------------------------------
    // Repeated updates on same range
    // --------------------------------
    n = 0;
    n_ptr = &n;

    u_setBitRange32(n_ptr, 4, WIDTH_MASK(4), 0xF);
    u_setBitRange32(n_ptr, 4, WIDTH_MASK(4), 0x3);

    expected = (0x3 << 4);
    passert(n == expected);
}

void test_u_getBitValue32(void) {
    ptest();

    uint32_t n;
    volatile uint32_t *n_ptr;

    // --------------------------------
    // Basic: reading a 1 bit
    // --------------------------------
    n = 0B0010000100011010;
    n_ptr = &n;

    passert(u_getBitValue32(n_ptr, 1) == true);
    passert(u_getBitValue32(n_ptr, 4) == true);
    printf("read 13\n");
    passert(u_getBitValue32(n_ptr, 13) == true);

    // --------------------------------
    // Basic: reading a 0 bit
    // --------------------------------
    passert(u_getBitValue32(n_ptr, 0) == false);
    passert(u_getBitValue32(n_ptr, 5) == false);
    passert(u_getBitValue32(n_ptr, 31) == false);

    // --------------------------------
    // LSB boundary
    // --------------------------------
    n = 1U;
    n_ptr = &n;

    passert(u_getBitValue32(n_ptr, 0) == true);
    passert(u_getBitValue32(n_ptr, 1) == false);

    // --------------------------------
    // MSB boundary
    // --------------------------------
    n = (1U << 31);
    n_ptr = &n;

    passert(u_getBitValue32(n_ptr, 31) == true);
    passert(u_getBitValue32(n_ptr, 30) == false);

    // --------------------------------
    // All zeros
    // --------------------------------
    n = 0;
    n_ptr = &n;

    for (int i = 0; i < 32; i++) {
        passert(u_getBitValue32(n_ptr, i) == false);
    }

    // --------------------------------
    // All ones
    // --------------------------------
    n = 0xFFFFFFFF;
    n_ptr = &n;

    for (int i = 0; i < 32; i++) {
        passert(u_getBitValue32(n_ptr, i) == true);
    }

    // --------------------------------
    // Stability: repeated reads
    // --------------------------------
    n = 0b10101010;
    n_ptr = &n;

    bool first = u_getBitValue32(n_ptr, 7);
    bool second = u_getBitValue32(n_ptr, 7);

    passert(first == second);
}

void test_u_getBitRangeValue32(void) {
    ptest();

    uint32_t n;
    volatile uint32_t *n_ptr;
    uint32_t result;

    // --------------------------------
    // Basic middle extraction
    // --------------------------------
    n = 0b1011010110101100;
    n_ptr = &n;

    // Extract bits 7–4 (should be 1011)
    result = u_getBitRangeValue32(n_ptr, 4, WIDTH_MASK(4));
    passert(result == 0b1010);

    // --------------------------------
    // Range at LSB boundary
    // --------------------------------
    n = 0b11010101;
    n_ptr = &n;

    result = u_getBitRangeValue32(n_ptr, 0, WIDTH_MASK(4));
    passert(result == 0b0101);

    // --------------------------------
    // Range at MSB boundary
    // --------------------------------
    n = 0;
    n |= (0b101 << 29);
    n_ptr = &n;

    result = u_getBitRangeValue32(n_ptr, 29, WIDTH_MASK(3));
    passert(result == 0b101);

    // --------------------------------
    // Should ignore surrounding bits
    // --------------------------------
    n = 0xF0AA0F0F;
    n_ptr = &n;

    result = u_getBitRangeValue32(n_ptr, 8, WIDTH_MASK(8));
    passert(result == 0x0F);

    // --------------------------------
    // Full-width read
    // --------------------------------
    n = 0x12345678;
    n_ptr = &n;

    result = u_getBitRangeValue32(n_ptr, 0, WIDTH_MASK(32));
    passert(result == 0x12345678);

    // --------------------------------
    // Single-bit range behaves like getBit
    // --------------------------------
    n = 0b10010000;
    n_ptr = &n;

    result = u_getBitRangeValue32(n_ptr, 7, WIDTH_MASK(1));
    passert(result == 1);

    result = u_getBitRangeValue32(n_ptr, 6, WIDTH_MASK(1));
    passert(result == 0);

    // --------------------------------
    // All zeros
    // --------------------------------
    n = 0;
    n_ptr = &n;

    result = u_getBitRangeValue32(n_ptr, 10, WIDTH_MASK(5));
    passert(result == 0);

    // --------------------------------
    // All ones
    // --------------------------------
    n = 0xFFFFFFFF;
    n_ptr = &n;

    result = u_getBitRangeValue32(n_ptr, 12, WIDTH_MASK(8));
    passert(result == WIDTH_MASK(8));

    // --------------------------------
    // Repeated reads should be stable
    // --------------------------------
    n = 0xABCDEFFF;
    n_ptr = &n;

    uint32_t first = u_getBitRangeValue32(n_ptr, 12, WIDTH_MASK(8));
    uint32_t second = u_getBitRangeValue32(n_ptr, 12, WIDTH_MASK(8));

    passert(first == second);
}

int main(void) {
    printf("BEGIN TEST FOR bin_util\n\n");
    test_u_setBit32();
    test_u_toggleBit32();
    test_u_setBitRange32();
    test_u_getBitValue32();
    test_u_getBitRangeValue32();
    return 0;
}
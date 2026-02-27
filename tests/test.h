#include <stdio.h>
#include <stdbool.h>

#define STR_OK          "[\x1b[1;32m OK \x1b[0m]"
#define STR_FAIL        "[\x1b[1;31mFAIL\x1b[0m]"

void passert(bool c) {
    int r = (c);
        if (r)
            printf(" " STR_OK "  %s %s():%d\n", __FILE__, __func__, __LINE__);
        else
            printf(" " STR_FAIL "  %s %s():%d\n", __FILE__, __func__, __LINE__);
}

void ptest() {
    printf("\nStarting test %s():%d\n", __func__, __LINE__);
}
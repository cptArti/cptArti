#include "next_even.h"

int64_t NextEven(int64_t n) {
    return static_cast<int64_t>(n - n % 2 + 2);
}

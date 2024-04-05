#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    if (n <= 0) {
        return 0;
    }

    int64_t fib[n + 1];
    fib[0] = 0;
    fib[1] = 1;

    for (int64_t i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return fib[n];
}

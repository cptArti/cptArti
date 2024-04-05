#include <numeric>
#include "reduce_fraction.h"

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t gcd = std::gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
    return numerator + denominator;
}

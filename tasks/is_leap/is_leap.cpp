#include "is_leap.h"

bool IsLeap(int year) {
    const int one_hundred = 100;
    const int four_hundred = 400;
    return ((year % 4 == 0 && year % one_hundred != 0) || year % four_hundred == 0);
}

#include "password.h"
#include "string"

bool ValidatePassword(const std::string& password) {
    uint64_t length = password.length();
    const int fourteen = 14;
    const int eight = 8;
    if (length < eight || length > fourteen) {
        return false;
    }
    int num_char_classes = 0;
    const int thirty_three = 33;
    const int one_hundred_twenty_six = 126;
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_other = false;
    for (int symbol = 0; symbol < length; ++symbol) {
        char char_symbol = password[symbol];
        if (char_symbol < thirty_three || char_symbol > one_hundred_twenty_six) {
            return false;
            break;
        }
        if (isupper(char_symbol)) {
            has_upper = true;
            ++num_char_classes;
        } else if (islower(char_symbol)) {
            has_lower = true;
            ++num_char_classes;
        } else if (isdigit(char_symbol)) {
            has_digit = true;
            ++num_char_classes;
        } else {
            has_other = true;
            ++num_char_classes;
        }
    }
    if (!has_digit) {
        if (!has_lower || !has_other || !has_upper) {
            return false;
        } else {
            return true;
        }
    } else if (!has_lower) {
        if (!has_digit || !has_other || !has_upper) {
            return false;
        } else {
            return true;
        }
    } else if (!has_other) {
        if (!has_lower || !has_digit || !has_upper) {
            return false;
        } else {
            return true;
        }
    } else if (!has_upper) {
        if (!has_lower || !has_other || !has_digit) {
            return false;
        } else {
            return true;
        }
    } else {
        return true;
    }
}

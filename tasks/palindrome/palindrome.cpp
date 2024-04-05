#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    if (str.empty()) {
        return true;
    }
    size_t left = 0;
    size_t right = str.size() - 1;
    while (left < right) {
        if (str[left] == ' ') {
            ++left;
        } else if (str[right] == ' ') {
            --right;
        } else if (str[left] == str[right]) {
            ++left;
            --right;
        } else {
            return false;
        }
    }
    return true;
}

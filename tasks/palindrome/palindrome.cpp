#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    if (str.empty()) {
        return true;
    }
    for (size_t i = 0, j = str.size() - 1; i < j;) {
        if (str[i] == ' ') {
            ++i;
        } else if (str[j] == ' ') {
            --j;
        } else if (str[i] != str[j]) {
            return false;
        } else {
            ++i;
            --j;
        }
    }
    return true;
}


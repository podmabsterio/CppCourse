#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    if (str.empty()) {
        return true;
    }
    for (size_t i = 0, j = str.size() - 1; i < j; ++i, --j) {
        for (;i < j && str[i] == ' '; ++i) {}
        for (;i < j && str[j] == ' '; --j) {}
        if (str[i] != str[j]) {
            return false;
        }
    }
    return true;
}

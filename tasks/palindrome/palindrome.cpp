#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    size_t j = str.size() - 1;
    for (size_t i = 0; i < j;) {
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

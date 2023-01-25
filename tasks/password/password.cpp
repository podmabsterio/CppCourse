#include "password.h"
#include <cctype>

const size_t MIN_LENGTH = 8;
const size_t MAX_LENGTH = 14;
const char MIN_CHARACTER = 33;
const char MAX_CHARACTER = 126;
const int8_t TYPES_REQUIRED = 3;

bool ValidatePassword(const std::string& password) {
    if (password.size() < MIN_LENGTH || password.size() > MAX_LENGTH) {
        return false;
    }
    int8_t has_upper_case = 0;
    int8_t has_lower_case = 0;
    int8_t has_digit = 0;
    int8_t has_other = 0;
    for (char ch : password) {
        if (ch > MAX_CHARACTER || ch < MIN_CHARACTER) {
            return false;
        } else if (std::islower(ch) != 0) {
            has_lower_case = 1;
        } else if (std::isupper(ch) != 0) {
            has_upper_case = 1;
        } else if (std::isdigit(ch) != 0) {
            has_digit = 1;
        } else {
            has_other = 1;
        }
    }
    return has_other + has_digit + has_lower_case + has_upper_case >= TYPES_REQUIRED;
}

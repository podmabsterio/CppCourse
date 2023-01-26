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
    bool has_upper_case = false;
    bool has_lower_case = false;
    bool has_digit = false;
    bool has_other = false;
    for (char ch : password) {
        if (ch > MAX_CHARACTER || ch < MIN_CHARACTER) {
            return false;
        } else if (std::islower(ch) != 0) {
            has_lower_case = true;
        } else if (std::isupper(ch) != 0) {
            has_upper_case = true;
        } else if (std::isdigit(ch) != 0) {
            has_digit = true;
        } else {
            has_other = true;
        }
    }
    return static_cast<int8_t>(has_other) + has_digit + has_lower_case + has_upper_case >= TYPES_REQUIRED;
}

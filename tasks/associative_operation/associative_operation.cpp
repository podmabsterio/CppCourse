#include "associative_operation.h"

bool IsAssociative(const std::vector<std::vector<size_t>>& table) {
    for (size_t x_elem = 0; x_elem < table.size(); ++x_elem) {
        if (table[x_elem].size() != table.size()) {
            return false;
        }
        for (size_t y_elem = 0; y_elem < table.size(); ++y_elem) {
            for (size_t z_elem = 0; z_elem < table.size(); ++z_elem) {
                if (table[x_elem][y_elem] >= table.size() || table[y_elem][z_elem] >= table.size()) {
                    return false;
                }
                const size_t &xy_result = table[x_elem][y_elem];
                const size_t &yz_result = table[y_elem][z_elem];
                if (table[xy_result][z_elem] != table[x_elem][yz_result]) {
                    return false;
                }
            }
        }
    }
    return true;
}

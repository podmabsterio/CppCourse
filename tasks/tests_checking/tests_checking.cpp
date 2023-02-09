#include "tests_checking.h"
#include <deque>


std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> order;
    for (auto& action : student_actions) {
        if (action.side == Side::Bottom) {
            order.emplace_back(action.name);
        } else {
            order.emplace_front(action.name);
        }
    }
    std::vector<std::string> name_list;
    for (auto place : queries) {
        name_list.emplace_back(order.at(place - 1));
    }
    return name_list;
}

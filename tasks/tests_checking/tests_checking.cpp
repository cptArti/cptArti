#include "tests_checking.h"

#include <deque>
#include <vector>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::vector<std::string> students_orders;
    std::deque<std::string> check_order;
    for (auto& action : student_actions) {
        if (action.side == Side::Top) {
            check_order.push_front(action.name);
        } else {
            check_order.push_back(action.name);
        }
    }
    for (size_t x : queries) {
        students_orders.push_back(check_order[x - 1]);
    }
    return students_orders;
}

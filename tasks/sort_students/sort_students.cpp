#include "sort_students.h"
#include <tuple>

bool CompareDate(const Student& a, const Student& b) {
    auto a_properties = std::tie(a.birth_date.year, a.birth_date.month, a.birth_date.day, a.last_name, a.name);
    auto b_properties = std::tie(b.birth_date.year, b.birth_date.month, b.birth_date.day, b.last_name, b.name);
    return a_properties < b_properties;
}

bool CompareName(const Student& a, const Student& b) {
    auto a_properties = std::tie(a.last_name, a.name, a.birth_date.year, a.birth_date.month, a.birth_date.day);
    auto b_properties = std::tie(b.last_name, b.name, b.birth_date.year, b.birth_date.month, b.birth_date.day);
    return a_properties < b_properties;
}

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    if (sortKind == SortKind::Date) {
        std::sort(students.begin(), students.end(), CompareDate);
    }
    else {
        std::sort(students.begin(), students.end(), CompareName);
    }
}

#include "admission.h"
#include <unordered_map>

bool CompareApplicants(const Applicant* a, const Applicant* b) {
    auto a_properties = std::tie(b->points, a->student.birth_date.year, a->student.birth_date.month,
                                 a->student.birth_date.day, a->student.name);
    auto b_properties = std::tie(a->points, b->student.birth_date.year, b->student.birth_date.month,
                                 b->student.birth_date.day, b->student.name);
    return a_properties < b_properties;
}

bool CompareStudents(const Student* a, const Student* b) {
    auto a_properties = std::tie(a->name, a->birth_date.year, a->birth_date.month, a->birth_date.day);
    auto b_properties = std::tie(b->name, b->birth_date.year, b->birth_date.month, b->birth_date.day);
    return a_properties < b_properties;
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<const Applicant*> sorted_applicants;
    for (size_t i = 0; i < applicants.size(); ++i) {
        sorted_applicants.emplace_back(&applicants[i]);
    }
    std::sort(sorted_applicants.begin(), sorted_applicants.end(), CompareApplicants);
    std::unordered_map<std::string, size_t> places_available;
    for (auto& university : universities) {
        places_available[university.name] = university.max_students;
    }
    AdmissionTable distribution;
    for (auto applicant : sorted_applicants) {
        for (auto& preffered_university : applicant->wish_list) {
            if (places_available[preffered_university] > 0) {
                --places_available[preffered_university];
                distribution[preffered_university].emplace_back(&applicant->student);
                break;
            }
        }
    }
    for (auto& [university_name, list_of_students] : distribution) {
        std::sort(list_of_students.begin(), list_of_students.end(), CompareStudents);
    }
    return distribution;
}

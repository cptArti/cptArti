#include "sort_students.h"

#include <algorithm>
void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    if (sortKind == SortKind::Date) {
        std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            if (a.birth_date.year != b.birth_date.year) return a.birth_date.year < b.birth_date.year;
            if (a.birth_date.month != b.birth_date.month) return a.birth_date.month < b.birth_date.month;
            if (a.birth_date.day != b.birth_date.day) return a.birth_date.day < b.birth_date.day;
            if (a.last_name != b.last_name) return a.last_name < b.last_name;
            return a.name < b.name;
        });
    } else if (sortKind == SortKind::Name) {
        std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            if (a.last_name != b.last_name) return a.last_name < b.last_name;
            if (a.name != b.name) return a.name < b.name;
            if (a.birth_date.year != b.birth_date.year) return a.birth_date.year < b.birth_date.year;
            if (a.birth_date.month != b.birth_date.month) return a.birth_date.month < b.birth_date.month;
            return a.birth_date.day < b.birth_date.day;
        });
    }
}

#include "calculations.h"
#include <iostream>

using namespace std;

bool compareByFirstName(const Student& a, const Student& b) {
    return a.getFirstName() < b.getFirstName();
}

bool compareByLastName(const Student& a, const Student& b) {
    return a.getLastName() < b.getLastName();
}

bool compareByGrade(const Student& a, const Student& b) {
    return a.calculateFinalGrade(false) < b.calculateFinalGrade(false);
}

template <typename Container>
void sortStudents(Container& students, int criteria) {
    if (criteria == 1) {
        sort(students.begin(), students.end(), compareByFirstName);
    } else if (criteria == 2) {
        sort(students.begin(), students.end(), compareByLastName);
    } else if (criteria == 3) {
        sort(students.begin(), students.end(), compareByGrade);
    }
}

template <>
void sortStudents<std::list<Student>>(std::list<Student>& students, int criteria) {
    if (criteria == 1) {
        students.sort(compareByFirstName);
    } else if (criteria == 2) {
        students.sort(compareByLastName);
    } else if (criteria == 3) {
        students.sort(compareByGrade);
    }
}

template void sortStudents<std::vector<Student>>(std::vector<Student>&, int);
template void sortStudents<std::deque<Student>>(std::deque<Student>&, int);
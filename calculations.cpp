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
    return calculateFinalGrade(a, false) < calculateFinalGrade(b, false);
}

double calculateAverage(const vector<int>& homeworkResults) {
    if (homeworkResults.empty()) {
        return 0;
    }
    double sum = 0;
    for (int i = 0; i < homeworkResults.size(); i++) {
        sum += homeworkResults[i];
    }
    return sum / homeworkResults.size();
}

double calculateFinalGrade(const Student& data, bool Median) {
    double homeworkGrade = Median ? calculateMedian(data.getHomeworkResults()) : calculateAverage(data.getHomeworkResults());
    return 0.4 * homeworkGrade + 0.6 * data.getExamResults();
}

double calculateMedian(vector<int> homeworkResults) {
    if (homeworkResults.empty()) {
        return 0;
    }
    sort(homeworkResults.begin(), homeworkResults.end());
    int size = homeworkResults.size();
    if (size % 2 == 0) { 
        return (homeworkResults[size / 2 - 1] + homeworkResults[size / 2]) / 2.0; 
    } else {
        return homeworkResults[size / 2];
    }
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
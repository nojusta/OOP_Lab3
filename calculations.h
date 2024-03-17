#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <vector>
#include "student.h" 
#include "input.h"

bool compareByFirstName(const Student& a, const Student& b);

bool compareByLastName(const Student& a, const Student& b);

bool compareByGrade(const Student& a, const Student& b);

double calculateAverage(const std::vector<int>& homeworkResults);

double calculateFinalGrade(const Student& data, bool Median);

double calculateMedian(std::vector<int> homeworkResults);

template <typename Container>
void sortStudents(Container& students, int criteria);

template <>
void sortStudents<std::list<Student>>(std::list<Student>& students, int criteria);

#endif // CALCULATIONS_H
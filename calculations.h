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

void sortStudents(std::vector<Student>& students, int criteria);

#endif // CALCULATIONS_H
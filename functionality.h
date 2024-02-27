#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

#include <string>
#include <vector>
#include "student.h" 
#include "calculations.h"

// Function declarations

int generateGrade();
std::string generateName();
std::string generateLastName();
std::string isString(const std::string& prompt);
int isGrade(const std::string& prompt);
void output(const std::vector<Student>& students, size_t size, bool Median);

#endif // FUNCTIONALITY_H
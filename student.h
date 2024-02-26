#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

struct Student {
    std::string firstName, lastName;
    std::vector<int> homeworkResults;
    int examResults;
};

#endif // STUDENT_H
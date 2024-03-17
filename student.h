#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <list>
#include <deque>

struct Student {
    std::string firstName, lastName;
    std::vector<int> homeworkResults;
    int examResults;
};

extern std::vector<Student> studentVector;
extern std::list<Student> studentList;
extern std::deque<Student> studentDeque;

#endif // STUDENT_H
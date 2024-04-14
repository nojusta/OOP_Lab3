#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <deque>
#include <list>

class Student { // klase Student
private:
    std::string firstName, lastName;
    std::vector<int> homeworkResults;
    int examResults;

public:

    Student(); // konstruktorius

    // konstruktorius su parametrais
    Student(const std::string& firstName, const std::string& lastName, int examResults, const std::vector<int>& homeworkResults); 

    // copy konstruktorius
    Student(const Student& other)
        : firstName(other.firstName), lastName(other.lastName),
          homeworkResults(other.homeworkResults), examResults(other.examResults) {}

    Student& operator=(const Student& other) { // priskyrimo operatorius
        if (this != &other) { // patikrinimas ar nera lygus pats sau 
            firstName = other.firstName; //
            lastName = other.lastName; 
            homeworkResults = other.homeworkResults;
            examResults = other.examResults;
        }
        return *this; // grazina objekta
    }

    ~Student() {} // destruktorius

    // geteriai ir seteriai 
    inline std::string getFirstName() const { return firstName; }
    inline std::string getLastName() const { return lastName; }
    inline std::vector<int> getHomeworkResults() const { return homeworkResults; }
    inline int getExamResults() const { return examResults; }

    void setFirstName(std::string firstName) { this->firstName = std::move(firstName); }
    void setLastName(std::string lastName) { this->lastName = std::move(lastName); }
    void addHomeworkResult(int result) { homeworkResults.push_back(result); }
    void clearHomeworkResults() { homeworkResults.clear(); }
    void setExamResults(int examResults) { this->examResults = examResults; }
    void setHomeworkResults(std::vector<int> results) { homeworkResults = std::move(results); }

    // funkcijos
    double calculateMedian() const;
    double calculateAverage() const;
    double calculateFinalGrade(bool median) const;
};

#endif // STUDENT_H
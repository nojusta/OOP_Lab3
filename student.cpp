#include "student.h"

Student::Student() : firstName(""), lastName(""), examResults(0) {} //  konstruktorius

//  konstruktorius su parametrais
Student::Student(const std::string& firstName, const std::string& lastName, int examResults, const std::vector<int>& homeworkResults)
    : firstName(firstName), lastName(lastName), examResults(examResults), homeworkResults(homeworkResults) {}

//  konstruktorius su parametrais
Student::Student(const Student& other)
    : firstName(other.firstName), lastName(other.lastName),
      homeworkResults(other.homeworkResults), examResults(other.examResults) {}

//  move konstruktorius
Student::Student(Student&& other) noexcept
    : firstName(std::move(other.firstName)), lastName(std::move(other.lastName)),
      homeworkResults(std::move(other.homeworkResults)), examResults(other.examResults) {}

//  copy konstruktorius
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        firstName = other.firstName;
        lastName = other.lastName;
        homeworkResults = other.homeworkResults;
        examResults = other.examResults;
    }
    return *this;
}

//  move konstruktorius
Student& Student::operator=(Student&& other) noexcept {
    if (this != &other) {
        firstName = std::move(other.firstName);
        lastName = std::move(other.lastName);
        homeworkResults = std::move(other.homeworkResults);
        examResults = other.examResults;
    }
    return *this;
}

// ivesties operatorius (nuskaitymui is failo)
std::istream& operator>>(std::istream& is, Student& s) {
    std::string tempFirstName, tempLastName;
    std::vector<int> grades;
    int grade;

    if (!(is >> tempFirstName >> tempLastName)) {
        return is;
    }
    s.setFirstName(tempFirstName);
    s.setLastName(tempLastName);

    while (is >> grade) {
        grades.push_back(grade);
    }

    // Clear the fail state if end of file is reached
    if (is.eof()) {
        is.clear();
    }

    if (!grades.empty()) {
        s.setExamResults(grades.back()); // Set the last grade as the exam result
        grades.pop_back(); // Remove the last grade from the homework results
    }
    s.setHomeworkResults(std::move(grades));

    return is;
}

// isvesties operatorius 
std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << std::setw(15) << s.getLastName() 
       << std::setw(15) << s.getFirstName();
    return os;
}

double Student::calculateAverage() const {
    if (homeworkResults.empty()) {
        return 0;
    }
    double sum = std::accumulate(homeworkResults.begin(), homeworkResults.end(), 0.0);
    return sum / homeworkResults.size();
}

double Student::calculateMedian() const { 
    if (homeworkResults.empty()) { 
        return 0;
    }
    std::vector<int> scores = homeworkResults; 
    std::sort(scores.begin(), scores.end()); 
    int size = scores.size(); 
    if (size % 2 == 0) { 
        return (scores[size / 2 - 1] + scores[size / 2]) / 2.0; 
    } else {
        return scores[size / 2];
    }
}

double Student::calculateFinalGrade(bool median) const { 
    double homeworkGrade = median ? calculateMedian() : calculateAverage();
    return 0.4 * homeworkGrade + 0.6 * examResults;
}

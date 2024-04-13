#include "student.h"

Student::Student() : firstName(""), lastName(""), examResults(0) {}

Student::Student(const std::string& firstName, const std::string& lastName, int examResults, const std::vector<int>& homeworkResults)
    : firstName(firstName), lastName(lastName), examResults(examResults), homeworkResults(homeworkResults) {}

double Student::calculateMedian() const {
    if (homeworkResults.empty()) {
        return 0;
    }
    std::vector<int> scores = homeworkResults;
    sort(scores.begin(), scores.end());
    int size = scores.size();
    if (size % 2 == 0) { 
        return (scores[size / 2 - 1] + scores[size / 2]) / 2.0; 
    } else {
        return scores[size / 2];
    }
}

double Student::calculateAverage() const {
    if (homeworkResults.empty()) {
        return 0;
    }
    double sum = 0;
    for (int i = 0; i < homeworkResults.size(); i++) {
        sum += homeworkResults[i];
    }
    return sum / homeworkResults.size();
}

double Student::calculateFinalGrade(bool median) const {
    double homeworkGrade = median ? calculateMedian() : calculateAverage();
    return 0.4 * homeworkGrade + 0.6 * examResults;
}
#include "student.h"
#include "input.h"
#include "calculations.h"
#include "functionality.h"

using namespace std;

std::vector<Student> studentVector;
std::list<Student> studentList;
std::deque<Student> studentDeque;

int main() {
    auto startTotal = chrono::high_resolution_clock::now();
    setlocale(LC_ALL, "lt_LT.UTF-8");
    srand(time(0));
    bool Median = getMedianPreference();

    int containerType = getContainerTypeFromUser();

    switch (containerType) {
        case 1:
            processStudents(studentVector, Median, startTotal);
            break;
        case 2:
            processStudents(studentDeque, Median, startTotal);
            break;
        case 3:
            processStudents(studentList, Median, startTotal);
            break;
    }

    return 0; 
}

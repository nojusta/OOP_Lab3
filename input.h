#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <vector>
#include <fstream>
#include "student.h" 
#include "calculations.h"
#include "functionality.h"

bool getMedianPreference();

template <typename Container>
void processStudents(Container& students, bool Median, std::chrono::high_resolution_clock::time_point startTotal);

int Menu();

std::string getFilenameFromUser();

void readData(std::ifstream& fin, std::vector<Student>& students);

void openFiles(const std::vector<std::string>& filenames, bool Median);

void input(Student& data, bool& Median);

#endif // INPUT_H
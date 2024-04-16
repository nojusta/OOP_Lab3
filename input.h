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

template <typename Container>
void readData(std::ifstream& fin, Container& students);

template <typename Container>
void openFiles(const std::vector<std::string>& filenames, Container& students, bool Median, int strategy);

void input(Student& data, bool& Median);

std::string studentData(const Student& s);

#endif // INPUT_H
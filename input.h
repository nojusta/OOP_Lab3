#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <vector>
#include <fstream>
#include "student.h" 
#include "calculations.h"
#include "functionality.h"

bool getMedianPreference();

void processStudents(std::vector<Student>& students, bool Median);

int Menu();

std::string getFilenameFromUser();

void readData(std::ifstream& fin, std::vector<Student>& students);

void openFiles(const std::vector<std::string>& filenames);

void input(Student& data, bool& Median);

#endif // INPUT_H
#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <deque>
#include <list>
#include <istream>
#include <ostream>
#include <iomanip>
#include <sstream>

class Human {
protected:
    std::string firstName;
    std::string lastName;

public:
    Human() = default;
    Human(const std::string& firstName, const std::string& lastName)
        : firstName(firstName), lastName(lastName) {}
    virtual ~Human() = default;

    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    std::string getName() const { return firstName + " " + lastName; }

    void setFirstName(const std::string& firstName) { this->firstName = firstName; }
    void setLastName(const std::string& lastName) { this->lastName = lastName; }
};

#endif // HUMAN_H
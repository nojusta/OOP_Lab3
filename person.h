#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <deque>
#include <list>
#include <cmath>
#include <istream>
#include <ostream>
#include <iomanip>
#include <sstream>
#include "myVector.h"

/**
 * @class Person
 * @brief Klasė, aprašanti žmogų.
 *
 * Ši klasė yra abstrakti bazinė klasė, nuo kurios paveldės Student klasė.
 */
class Person {
public:
    /**
     * @brief Virtualus destruktorius.
     */
    virtual ~Person() = default;

    /**
     * @brief Virtualus metodas, grąžinantis asmens vardą.
     * @return Asmens vardas.
     */
    virtual std::string getFirstName() const = 0;

    /**
     * @brief Virtualus metodas, grąžinantis asmens pavardę.
     * @return Asmens pavardė.
     */
    virtual std::string getLastName() const = 0;

    /**
     * @brief Virtualus metodas, grąžinantis pilną asmens vardą ir pavardę.
     * @return Pilnas asmens vardas ir pavardė.
     */
    virtual std::string getName() const = 0;
};

#endif // PERSON_H
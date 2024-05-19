#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"

/**
 * @class Student
 * @brief Klasė, aprašanti studentą.
 *
 * Ši klasė paveldi Person klasę ir prideda papildomus studento atributus.
 */
class Student : public Person {
private:
    std::string firstName, lastName; ///< Studento vardas ir pavardė.
    std::vector<int> homeworkResults; ///< Namų darbų rezultatai.
    int examResults; ///< Egzamino rezultatas.

public:
    /**
     * @brief Konstruktorius be parametrų.
     */
    Student();

    /**
     * @brief Konstruktorius su parametrais.
     * @param firstName Studento vardas.
     * @param lastName Studento pavardė.
     * @param examResults Studento gzamino rezultatas.
     * @param homeworkResults Studento namų darbų rezultatai.
     */
    Student(const std::string &firstName, const std::string &lastName, int examResults, const std::vector<int> &homeworkResults);

    /**
     * @brief Kopijavimo konstruktorius.
     * @param other Kita Student klasės objekto instancija.
     */
    Student(const Student &other);

    /**
     * @brief Perkėlimo konstruktorius.
     * @param other Kita Student klasės objekto instancija.
     */
    Student(Student &&other) noexcept;

    /**
     * @brief Kopijavimo priskyrimo operatorius.
     * @param other Kita Student klasės objekto instancija.
     * @return Grąžina *this.
     */
    Student &operator=(const Student &other);

    /**
     * @brief Perkėlimo priskyrimo operatorius.
     * @param other Kita Student klasės objekto instancija.
     * @return Grąžina *this.
     */
    Student &operator=(Student &&other) noexcept;

    /**
     * @brief Įvesties operatorius.
     * @param is Įvesties srautas.
     * @param s Student klasės objekto instancija.
     * @return Grąžina įvesties srautą.
     */
    friend std::istream &operator>>(std::istream &is, Student &s);

    /**
     * @brief Išvesties operatorius.
     * @param os Išvesties srautas.
     * @param s Student klasės objekto instancija.
     * @return Grąžina išvesties srautą.
     */
    friend std::ostream &operator<<(std::ostream &os, const Student &s);

    /**
     * @brief Destruktorius.
     */
    ~Student() {
        homeworkResults.clear();
    }

    // Get'eriai
    /**
     * @brief Grąžina studento vardą.
     * @return Studento vardas.
     */
    inline std::string getFirstName() const { return firstName; }

    /**
     * @brief Grąžina studento pavardę.
     * @return Studento pavardė.
     */
    inline std::string getLastName() const { return lastName; }

    /**
     * @brief Grąžina studento vardą ir pavardę.
     * @return Studento vardas ir pavardė.
     */
    std::string getName() const { return getFirstName() + " " + getLastName(); }

    /**
     * @brief Grąžina studento namų darbų rezultatus.
     * @return Namų darbų rezultatai.
     */
    const std::vector<int> &getHomeworkResults() const { return homeworkResults; }

    /**
     * @brief Grąžina studento egzamino rezultatą.
     * @return Egzamino rezultatas.
     */
    int getExamResults() const { return examResults; }

    /**
     * @brief Grąžina studento egzamino pažymį.
     * @return Egzamino pažymys.
     */
    int getExamGrade() const { return homeworkResults.back(); }

    /**
     * @brief Pašalina paskutinį namų darbo pažymį.
     */
    void removeLastHomeworkGrade() { if (!homeworkResults.empty()) { homeworkResults.pop_back(); } }

    // Set'eriai
    /**
     * @brief Nustato studento vardą.
     * @param firstName Studento vardas.
     */
    void setFirstName(std::string firstName) { this->firstName = std::move(firstName); }

    /**
     * @brief Nustato studento pavardę.
     * @param lastName Studento pavardė.
     */
    void setLastName(std::string lastName) { this->lastName = std::move(lastName); }

    /**
     * @brief Prideda namų darbo rezultatą.
     * @param result Namų darbo rezultatas.
     */
    void addHomeworkResult(int result) { homeworkResults.push_back(result); }

    /**
     * @brief Išvalo namų darbų rezultatus.
     */
    void clearHomeworkResults() { homeworkResults.clear(); }

    /**
     * @brief Nustato egzamino rezultatą.
     * @param examResults Egzamino rezultatas.
     */
    void setExamResults(int examResults) { this->examResults = examResults; }

    /**
     * @brief Nustato namų darbų rezultatus.
     * @param results Namų darbų rezultatai.
     */
    void setHomeworkResults(std::vector<int> results) { homeworkResults = std::move(results); }

    // Funkcijos
    /**
     * @brief Skaičiuoja medianą iš namų darbų rezultatų.
     * @return Mediana.
     */
    double calculateMedian() const;

    /**
     * @brief Skaičiuoja vidurkį iš namų darbų rezultatų.
     * @return Vidurkis.
     */
    double calculateAverage() const;

    /**
     * @brief Skaičiuoja galutinį pažymį.
     * @param median Jei true, naudoja medianą, jei false, naudoja vidurkį.
     * @return Galutinis pažymys.
     */
    double calculateFinalGrade(bool median) const;
};

#endif // STUDENT_H
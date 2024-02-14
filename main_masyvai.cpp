#include <iostream>
#include <iomanip>
#include <string> 
#include <algorithm> 
#include <limits>
#include <random> 
#include <ctime>

using namespace std;

struct Student {
    string firstName, lastName;
    int* homeworkResults;
    int homeworkCount;
    int examResults;
};

int Menu();

int generateGrade();

string generateName();

string generateLastName();

string isString(const string& prompt);

int isGrade(const string& prompt);

void input(Student& data, bool& Median);

double calculateAverage(const int* homeworkResults, int homeworkCount);

double calculateFinalGrade(const Student& data, bool Median);

double calculateMedian(int* homeworkResults, int homeworkCount);

void output(Student* students, const int & m, bool Median);

int main() {
    srand(time(0));
    Student* students = new Student[1]; 
    bool Median;
    cout << "Ar norite galutinio balo skaiciavimui naudoti mediana? (1 - taip, 0 - ne): ";
    cin >> Median;
    int studentCount = 0;
    int moreStudents;
    int number;
    do {
        number = Menu();
        switch (number) {
            case 1: {
                do {
                    input(students[studentCount], Median);
                    studentCount++;
                    Student* temp = new Student[studentCount + 1]; 
                    for (int i = 0; i < studentCount; i++) {
                        temp[i] = students[i]; 
                    }
                    delete[] students;
                    students = temp;
                    cout << "Ar norite ivesti dar viena studenta? (1 - taip, 0 - ne): ";
                    cin >> moreStudents;
                } while (moreStudents == 1);
                break;
            }
            case 2: {
                do {
                    cout << "Iveskite studento varda: ";
                    cin >> students[studentCount].firstName;
                    cout << "Iveskite studento pavarde: ";
                    cin >> students[studentCount].lastName;
                    students[studentCount].homeworkResults = new int[5];
                    for (int j = 0; j < 5; j++) {
                        students[studentCount].homeworkResults[j] = generateGrade();
                    }
                    students[studentCount].homeworkCount = 5;
                    students[studentCount].examResults = generateGrade();
                    studentCount++;
                    Student* temp = new Student[studentCount + 1]; 
                    for (int i = 0; i < studentCount; i++) {
                        temp[i] = students[i]; 
                    }
                    delete[] students;
                    students = temp;
                    cout << "Ar norite ivesti dar viena studenta? (1 - taip, 0 - ne): ";
                    cin >> moreStudents;
                } while (moreStudents == 1);
                break;
            }
            case 3: {
                do {
                    students[studentCount].firstName = generateName();
                    students[studentCount].lastName = generateLastName();
                    students[studentCount].homeworkResults = new int[5];
                    for (int i = 0; i < 5; i++) {
                        students[studentCount].homeworkResults[i] = generateGrade();
                    }
                    students[studentCount].homeworkCount = 5;
                    students[studentCount].examResults = generateGrade();
                    studentCount++;
                    Student* temp = new Student[studentCount + 1]; 
                    for (int i = 0; i < studentCount; i++) {
                        temp[i] = students[i]; 
                    }
                    delete[] students;
                    students = temp;
                    cout << "Ar norite ivesti dar viena studenta? (1 - taip, 0 - ne): ";
                    cin >> moreStudents;
                } while (moreStudents == 1);
                break;
            }
            case 4: {
                break;
            }
            default: {
                cout << "Netinkama ivestis, iveskite skaiciu tarp 1 ir 4.\n";
                break;
            }
        }
    } while (number != 4);
    if (studentCount > 0) {
        output(students, studentCount, Median);
    }
    for (int i = 0; i < studentCount; i++) {
        delete[] students[i].homeworkResults; 
    }
    delete[] students;
    return 0;
}

int Menu() {
    int number;
    cout << "1 - Suvesti duomenis ranka\n";
    cout << "2 - Generuoti pazymius\n";
    cout << "3 - Generuoti ir pazymius ir studentu vardus, pavardes\n";
    cout << "4 - baigti darba\n";
    cout << "Iveskite skaiciu: ";
    cin >> number;
    return number;
}

int generateGrade() {
    return rand() % 10 + 1; // grazina skaiciu nuo 1 iki 10 (pazymi)
}

string generateName() {
    string names[] = {"Jonas", "Tomas", "Rokas", "Lukas", "Mantas", "Arvydas"};
    return names[rand() % 6];
}

string generateLastName() {
    string lastNames[] = {"Kazlauskas", "Sabonis", "Stankevicius", "Petrauskas", "Navickas", "Urbonas"};
    return lastNames[rand() % 6]; 
}

string isString(const string& prompt) {
    string result;
    do {
        cout << prompt;
        cin >> result;
        if (!all_of(result.begin(), result.end(), ::isalpha)) { // patikrina ar ivestis yra tik is raidziu
            cout << "Netinkama ivestis, nenaudokite skaiciu." << endl;
        } else {
            break; // jei ivestis yra is raidziu, nutraukia cikla
        }
    } while (true);
    return result;
}

int isGrade(const string& prompt) {
    int result;
    while (true) {
        cout << prompt;
        cin >> result;
        if (cin.fail()) { // patikrina ar ivestis yra skaicius ir ar jis yra nuo 1 iki 10
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Netinkama ivestis, iveskite skaiciu nuo 1 iki 10 arba -1 jei baigete." << endl; 
        } else if(result == -1) {
            return result;
        } else if(result < 1 || result > 10){
            cout << "Netinkama ivestis, iveskite skaiciu nuo 1 iki 10 arba -1 jei baigete." << endl;
        } else {
            return result;
        }
    } 
}

void input(Student& data, bool& Median){
    data.firstName = isString("Iveskite studento varda: ");
    data.lastName = isString("Iveskite studento pavarde: ");
    data.homeworkCount = 0;
    data.homeworkResults = new int[1];
    while (true) {
        int result = isGrade("Iveskite namu darbo pazymi arba -1, jei baigete: ");
        if (result == -1) {
            break;
        }
        data.homeworkResults[data.homeworkCount] = result;
        data.homeworkCount++;
        int* temp = new int[data.homeworkCount + 1];
        for (int i = 0; i < data.homeworkCount; i++) {
            temp[i] = data.homeworkResults[i];
        }
        delete[] data.homeworkResults;
        data.homeworkResults = temp;
    }
    data.examResults = isGrade("Iveskite studento egzamino rezultata: ");
}

double calculateAverage(const int* homeworkResults, int homeworkCount) {
    if (homeworkCount == 0) {
        return 0; // jei masyvas tuscias, grazina 0
    }
    double sum = 0;
    for (int i = 0; i < homeworkCount; i++) {
        sum += homeworkResults[i];
    }
    return sum / homeworkCount;
}

double calculateFinalGrade(const Student& data, bool Median) {
    double homeworkGrade = Median ? calculateMedian(data.homeworkResults, data.homeworkCount) : calculateAverage(data.homeworkResults, data.homeworkCount); // jei Median = true, naudoja mediana, jei ne, naudoja vidurki
    return 0.4 * homeworkGrade + 0.6 * data.examResults;
}

double calculateMedian(int* homeworkResults, int homeworkCount) {
    if (homeworkCount == 0) {
        return 0; // jei masyvas tuscias, grazina 0
    }
    sort(homeworkResults, homeworkResults + homeworkCount); // surusiuoja masyva didejimo tvarka 
    if (homeworkCount % 2 == 0) { 
        return (homeworkResults[homeworkCount / 2 - 1] + homeworkResults[homeworkCount / 2]) / 2.0; 
    } else {
        return homeworkResults[homeworkCount / 2];
    }
}

void output(Student* students, const int & m, bool Median){
    cout << "\n" << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
    cout << "-------------------------------------------------------" << endl;
    for (int i = 0; i < m; i++) {
        double finalGrade = calculateFinalGrade(students[i], Median);
        cout << setw(15) << students[i].lastName << setw(15) << students[i].firstName << fixed << setprecision(2) << finalGrade << endl;
    }
}
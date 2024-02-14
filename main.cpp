#include <iostream>
#include <vector>
#include <iomanip>
#include <string> 
#include <algorithm> 
#include <limits>
#include <random> 
#include <ctime>

using namespace std;

struct Student {
    string firstName, lastName;
    vector<int> homeworkResults;
    int examResults;
};

int Menu();

int generateGrade();

string generateName();

string generateLastName();

string isString(const string& prompt);

int isGrade(const string& prompt);

void input(Student& data, bool& Median);

double calculateAverage(const vector<int>& homeworkResults);

double calculateFinalGrade(const Student& data, bool Median);

double calculateMedian(vector<int> homeworkResults);

void output(const vector<Student>& students, const int & m, bool Median);

int main() {
    srand(time(0));
    Student data;
    bool Median;
    cout << "Ar norite galutinio balo skaiciavimui naudoti mediana? (1 - taip, 0 - ne): ";
    cin >> Median;
    vector<Student> students;
    int number;
    int moreStudents;
    do {
        number = Menu();
        switch (number) {
            case 1: {
                do {
                    input(data, Median);
                    students.push_back(data);
                    cout << "Ar norite ivesti dar viena studenta? (1 - taip, 0 - ne): ";
                    cin >> moreStudents;
                } while (moreStudents == 1);
                break;
            }
            case 2: {
                do {
                    cout << "Iveskite studento varda: ";
                    cin >> data.firstName;
                    cout << "Iveskite studento pavarde: ";
                    cin >> data.lastName;
                    for (int j = 0; j < 5; j++) {
                        data.homeworkResults.push_back(generateGrade());
                    }
                    data.examResults = generateGrade();
                    students.push_back(data);
                    cout << "Ar norite ivesti dar viena studenta? (1 - taip, 0 - ne): ";
                    cin >> moreStudents;
                } while (moreStudents == 1);
                break;
            }
            case 3: {
                do {
                    data.firstName = generateName();
                    data.lastName = generateLastName();
                    for (int i = 0; i < 5; i++) {
                        data.homeworkResults.push_back(generateGrade());
                    }
                    data.examResults = generateGrade();
                    students.push_back(data);
                    cout << "Ar norite sugeneruoti dar vieno studento duomenis? (1 - taip, 0 - ne): ";
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
    if (!students.empty()) {
        output(students, students.size(), Median);
    }
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
    data.homeworkResults.clear(); // patikrina ar vektorius yra tuscias ir isvalo ji
    while (true) {
        int result = isGrade("Iveskite namu darbo pazymi arba -1, jei baigete: ");
        if (result == -1) {
            break;
        }
        data.homeworkResults.push_back(result);
    }
    data.examResults = isGrade("Iveskite studento egzamino rezultata: ");
}

double calculateAverage(const vector<int>& homeworkResults) {
    if (homeworkResults.empty()) {
        return 0; // jei vektorius tuscias, grazina 0
    }
    double sum = 0;
    for (int i = 0; i < homeworkResults.size(); i++) {
        sum += homeworkResults[i];
    }
    return sum / homeworkResults.size();
}

double calculateFinalGrade(const Student& data, bool Median) {
    double homeworkGrade = Median ? calculateMedian(data.homeworkResults) : calculateAverage(data.homeworkResults); // jei Median = true, naudoja mediana, jei ne, naudoja vidurki
    return 0.4 * homeworkGrade + 0.6 * data.examResults;
}

double calculateMedian(vector<int> homeworkResults) {
    if (homeworkResults.empty()) {
        return 0; // jei vektorius tuscias, grazina 0
    }
    sort(homeworkResults.begin(), homeworkResults.end()); // surusiuoja vektoriu didejimo tvarka 
    int size = homeworkResults.size();
    if (size % 2 == 0) { 
        return (homeworkResults[size / 2 - 1] + homeworkResults[size / 2]) / 2.0; 
    } else {
        return homeworkResults[size / 2];
    }
}

void output(const vector<Student>& students, const int & m, bool Median){
    cout << "\n" << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
    cout << "-------------------------------------------------------" << endl;
    for (int i = 0; i < m; i++) {
        double finalGrade = calculateFinalGrade(students[i], Median);
        cout << setw(15) << students[i].lastName << setw(15) << students[i].firstName << fixed << setprecision(2) << finalGrade << endl;
    }
}
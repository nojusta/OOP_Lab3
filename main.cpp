#include <iostream>
#include <vector>
#include <iomanip>
#include <string> 
#include <algorithm> 
#include <limits>

using namespace std;

struct Student {
    string firstName, lastName;
    vector<int> homeworkResults;
    int examResults;
};

string isString(const string& prompt);

int isNumber(const string& prompt);

int isGrade(const string& prompt);

void input(Student& data, bool& Median);

double calculateAverage(const vector<int>& homeworkResults);

double calculateFinalGrade(const Student& data, bool Median);

double calculateMedian(vector<int> homeworkResults);

void output(const vector<Student>& students, int & m, bool Median);

int main() {
    Student data;
    int m = isNumber("Iveskite studentu skaiciu: ");
    bool Median;
    cout << "Ar norite galutinio balo skaiciavimui naudoti mediana? (1 - taip, 0 - ne): ";
    cin >> Median;
    vector<Student> students(m);
    for (int i = 0; i < m; i++) {
        input(students[i], Median);
    }
    output(students, m, Median);
    return 0;
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

int isNumber(const string& prompt) {
    int result;
    do {
        cout << prompt;
        cin >> result;
        if (cin.fail()) { // patikrina ar ivestis yra skaicius
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // istrina klaidinga ivesti
            cout << "Netinkama ivestis, iveskite skaiciu." << endl; 
        } else {
            break; // jei ivestis yra skaicius, nutraukia cikla 
        }
    } while (true);
    return result;
}

int isGrade(const string& prompt) {
    int result;
    do {
        cout << prompt;
        cin >> result;
        if (cin.fail() || result < 1 || result > 10) { // patikrina ar ivestis yra skaicius ir ar jis yra nuo 1 iki 10
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Netinkama ivestis, iveskite pazymi nuo 1 iki 10." << endl; 
        } else {
            break;
        }
    } while (true);
    return result;
}

void input(Student& data, bool& Median){
    data.firstName = isString("Iveskite studento varda: ");
    data.lastName = isString("Iveskite studento pavarde: ");
    int n = isNumber("Iveskite studento namu darbu kieki (n): ");
    data.homeworkResults.clear(); // patikrina ar vektorius yra tuscias ir isvalo ji
    for (int i = 0; i < n; i++) {
        int result = isGrade("Iveskite " + to_string(i + 1) + " namu darbo rezultata: ");
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
    double homeworkGrade = Median ? calculateMedian(data.homeworkResults) : calculateAverage(data.homeworkResults);
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

void output(const vector<Student>& students, int & m, bool Median) {
    cout << "\n" << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl;
    cout << "-------------------------------------------------------" << endl;
    for (int i = 0; i < m; i++) {
        double finalGrade = calculateFinalGrade(students[i], Median);
        cout << setw(15) << students[i].lastName << setw(15) << students[i].firstName << fixed << setprecision(2) << finalGrade << endl;
    }
}
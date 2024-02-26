#include <iostream>
#include <vector>
#include <iomanip>
#include <string> 
#include <algorithm> 
#include <limits>
#include <random> 
#include <ctime>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <exception>
#include <locale.h>
#include "student.h"

using namespace std;

int Menu();

string getFilenameFromUser();

void readData(ifstream& fin, vector<Student>& students);

void openFiles(const vector<string>& filenames);

int generateGrade();

string generateName();

string generateLastName();

string isString(const string& prompt);

int isGrade(const string& prompt);

void input(Student& data, bool& Median);

double calculateAverage(const vector<int>& homeworkResults);

double calculateFinalGrade(const Student& data, bool Median);

double calculateMedian(vector<int> homeworkResults);

bool compareByFirstName(const Student& a, const Student& b);

bool compareByLastName(const Student& a, const Student& b);

bool compareByGrade(const Student& a, const Student& b);

int countLithuanianLetters(const string& s);

void sortStudents(vector<Student>& students, int criteria);

void output(const vector<Student>& students, const int & m, bool Median);

int main() {
    setlocale(LC_ALL, "lt_LT.UTF-8");
    srand(time(0));
    Student data;
    bool Median;
    string a;
    while (true) {
        try {
            cout << "Ar norite galutinio balo skaičiavimui naudoti medianą? (1 - taip, 0 - ne): ";
            cin >> a;
            if (a == "0") {
                Median = false;
                break;
            } else if (a == "1") {
                Median = true;
                break;
            } else {
                throw invalid_argument("Neteisinga įvestis. Prašome įvesti 0 arba 1.");
            }
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }
    vector<Student> students;
    int number;
    int moreStudents;
    do {
        try {
            number = Menu();
        } catch (const exception& e) {
            cerr << "Įvyko klaida: " << e.what() << '\n';
            continue;
        }
        switch (number) {
            case 1: {
                do {
                    try {
                        input(data, Median);
                        students.push_back(data);
                    } catch (const exception& e) {
                        cerr << e.what() << '\n';
                    }
                    while (true) { 
                        cout << "Ar norite sugeneruoti dar vieno studento pažymius? (1 - taip, 0 - ne): ";
                        cin >> moreStudents;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cerr << "Neteisinga įvestis. Prašome įvesti 0 arba 1." << endl;
                        } else if (moreStudents == 0 || moreStudents == 1) {
                            break; 
                        } else {
                            cerr << "Neteisinga įvestis. Prašome įvesti 0 arba 1." << endl;
                        }
                    }
                } while (moreStudents == 1);
                break;
            }
            case 2: {
                do {
                    try {
                        data.firstName = isString("Įveskite studento vardą: ");
                        data.lastName = isString("Įveskite studento pavardę: ");
                        for (int j = 0; j < 5; j++) {
                            data.homeworkResults.push_back(generateGrade());
                        }
                        data.examResults = generateGrade();
                        students.push_back(data);
                        while (true) { 
                            cout << "Ar norite sugeneruoti dar vieno studento pažymius? (1 - taip, 0 - ne): ";
                            cin >> moreStudents;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cerr << "Neteisinga įvestis. Prašome įvesti 0 arba 1." << endl;
                            } else if (moreStudents == 0 || moreStudents == 1) {
                                break; 
                            } else {
                                cerr << "Neteisinga įvestis. Prašome įvesti 0 arba 1." << endl;
                            }
                        }
                    } catch (const exception& e) {
                        cerr << "Įvyko klaida: " << e.what() << '\n';
                    }
                } while (moreStudents == 1);
                break;
            }
            case 3: {
                int numStudents;
                while (true) {
                    try {
                        cout << "Įveskite kiek studentų duomenų norite sugeneruoti: ";
                        cin >> numStudents;
                        if (cin.fail() || numStudents < 1) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            throw invalid_argument("Neteisinga įvestis. Prašome įvesti teigiamą skaičių.");
                        }
                        break;
                    } catch (const exception& e) {
                        cerr << "Įvyko klaida: " << e.what() << '\n';
                    }
                }
                for (int i = 0; i < numStudents; i++) {
                    data.firstName = generateName();
                    data.lastName = generateLastName();
                    for (int j = 0; j < 5; j++) {
                        data.homeworkResults.push_back(generateGrade());
                    }
                    data.examResults = generateGrade();
                    students.push_back(data);
                }
                break;
            }
            case 4: {
                try {
                    string filename = getFilenameFromUser();
                    ifstream fin(filename); 
                    cout << "\nFailas " << '"' << filename << '"' << " nuskaitytas sėkmingai." << endl;
                    readData(fin, students);
                } catch (const runtime_error& e) {
                    cerr << e.what() << '\n';
                } catch (const exception& e) {
                    cerr << "Įvyko klaida: " << e.what() << '\n';
                }
                break;
            }
            case 5: {
                try {
                    string filename = getFilenameFromUser();
                    ifstream fin(filename); 
                    cout << "\nFailas " << '"' << filename << '"' << " atidarytas sėkmingai." << endl;
                    vector<string> filenames;
                    filenames.push_back(filename);
                    openFiles(filenames);
                } catch (const runtime_error& e) {
                    cerr << e.what() << '\n';
                } catch (const exception& e) {
                    cerr << "Įvyko klaida: " << e.what() << '\n';
                }
                break;
            }
            case 6: {
                if (!students.empty()) {
                    cout << "Įveskite kaip norite išrušiuoti studentus: 1 - pagal vardą, 2 - pagal pavardę, 3 - pagal galutinį balą: ";
                    int criteria;
                    while(true) {
                        try {
                            cin >> criteria;
                            if(cin.fail()) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                throw runtime_error("Netinkama įvestis, įveskite skaičių 1, 2 arba 3.");
                            }
                            if (criteria != 1 && criteria != 2 && criteria != 3) {
                                throw runtime_error("Netinkama įvestis, įveskite skaičių 1, 2 arba 3.");
                            }
                            break;
                        } catch (const runtime_error& e) {
                            cout << e.what() << endl;
                        }
                    }
                    try {
                        sortStudents(students, criteria);
                        output(students, students.size(), Median);
                    } catch (const exception& e) {
                        cerr << "Įvyko klaida rušiuojant / išvedant studentus \n";
                    }
                } 
                break;
            }
        }
    } while (number != 6);
    
    return 0;
}

int Menu() {
    int number;
    cout << "\n1 - Suvesti duomenis ranka\n";
    cout << "2 - Generuoti pažymius\n";
    cout << "3 - Generuoti ir pažymius ir studentų vardus, pavardes\n";
    cout << "4 - Skaityti duomenis iš failo\n";
    cout << "5 - Atidaryti testavimo failus\n";
    cout << "6 - Baigti darbą / Išvedimas\n";
    cout << "\nĮveskite skaičių: ";
    cin >> number;
    if (number < 1 || number > 6) {
        throw runtime_error("Netinkama įvestis, įveskite skaičių tarp 1 ir 6.");
    }
    return number;
}

string getFilenameFromUser() {
    cout << "Įveskite norimo failo pavadinimą (kursiokai.txt, studentai10000.txt, studentai100000.txt, studentai1000000.txt): \n";
    string filename;
    cin >> filename;
    ifstream fin(filename);
    if (!fin) {
        throw runtime_error("Failas " + filename + " nerastas.");
    }
    return filename;
}

void readData(ifstream& fin, vector<Student>& students) {
    string buffer; 
    getline(fin, buffer); // nuskaitome pirma eilute, nes joje yra tik antrastes
    while (getline(fin, buffer)) { // skaitome faila eilute po eilutes
        stringstream ss(buffer); 
        vector<int> grades;
        Student s; 
        ss >> s.firstName >> s.lastName; 
        int grade;
        while (ss >> grade) { // skaitome pazymius is eilutes
            grades.push_back(grade);
        }
        if (ss.fail() && !ss.eof()) { // patikriname ar nuskaitymas pavyko
            throw runtime_error("Nepavyko nuskaityti pažymio.");
        }
        if (!grades.empty()) {
            s.examResults = grades.back(); // paskutinis nuskaitytas skaicius yra egzamino pazymys
            grades.pop_back(); // istriname egzamino pazymi is vektoriaus
        }   
        s.homeworkResults = grades; // priskiriame namu darbu pazymiams
        students.push_back(s); // pridedame studenta i vektoriu
    }
}

void openFiles(const vector<string>& filenames) {
    int numTests = 3; 
    double sum = 0.0;
    for (vector<string>::const_iterator it = filenames.begin(); it != filenames.end(); ++it) { 
        ifstream fin(*it); 
        for (int test = 0; test < numTests; ++test) {
            clock_t start = clock(); 
            vector<Student> students;
            readData(fin, students);
            clock_t end = clock(); 
            double sec = double(end - start) / CLOCKS_PER_SEC; 
            sum += sec; 
            fin.clear(); 
            fin.seekg(0); 
        }
        fin.close();
    }
    double average = sum / (filenames.size() * numTests); 
    cout << "\nKelių testų laikų vidurkis: " << average << " sekundės" << endl;
}

int generateGrade() {
    return rand() % 10 + 1; // grazina skaiciu nuo 1 iki 10 (pazymi)
}

string generateName() {
    string names[] = {"Jonas", "Tomas", "Rokas", "Lukas", "Mantas", "Arvydas"};
    return names[rand() % 6];
}

string generateLastName() {
    string lastNames[] = {"Kazlauskas", "Sabonis", "Stankevičius", "Petrauskas", "Navickas", "Urbonas"};
    return lastNames[rand() % 6]; 
}

string isString(const string& prompt) {
    while (true) {
        try {
            string result;
            cout << prompt;
            cin >> result;
            if (!all_of(result.begin(), result.end(), ::isalpha)) { // patikrina ar ivestis yra tik is raidziu
                throw runtime_error("Netinkama įvestis, nenaudokite skaičių.");
            }
            return result;
        } catch (const runtime_error& e) {
            cerr << e.what() << '\n';
        }
    }
}

int isGrade(const string& prompt) {
    while (true) {
        try {
            int result;
            cout << prompt;
            cin >> result;
            if (cin.fail() || cin.peek() != '\n' || (result < 1 && result != -1) || result > 10) { // check if input is a number and if it's between 1 and 10 or -1
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Netinkama įvestis, įveskite sveiką skaičių nuo 1 iki 10 arba -1 jei baigėte."); 
            }
            return result;
        } catch (const runtime_error& e) {
            cerr << e.what() << '\n';
        }
    }
}

void input(Student& data, bool& Median){
    data.firstName = isString("Įveskite studento vardą: ");
    data.lastName = isString("Įveskite studento pavardę: ");
    data.homeworkResults.clear(); // isvalome vektoriu
    while (true) {
        int result = isGrade("Įveskite namų darbo pažymį arba -1, jei baigėte: ");
        if (result == -1) {
            break;
        }
        data.homeworkResults.push_back(result);
    }
    data.examResults = isGrade("Įveskite studento egzamino rezultatą: ");
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

bool compareByFirstName(const Student& a, const Student& b) {
    return a.firstName < b.firstName;
}

bool compareByLastName(const Student& a, const Student& b) {
    return a.lastName < b.lastName;
}

bool compareByGrade(const Student& a, const Student& b) {
    return calculateFinalGrade(a, false) < calculateFinalGrade(b, false);
}

int countLithuanianLetters(const string& s) {
    string lithuanianLetters = "ąčęėįšųūžĄČĘĖĮŠŲŪŽ";
    int count = 0;
    for (size_t i = 0; i < s.length(); i++) {
        char c = s[i];
        if (lithuanianLetters.find(c) != string::npos) {
            count++;
        }
    }
    return count;
}

void sortStudents(vector<Student>& students, int criteria) {
    if (criteria == 1) {
        sort(students.begin(), students.end(), compareByFirstName);
    } else if (criteria == 2) {
        sort(students.begin(), students.end(), compareByLastName);
    } else if (criteria == 3) {
        sort(students.begin(), students.end(), compareByGrade);
    }
}

void output(const vector<Student>& students, const int & m, bool Median){
    int choice;
    while (true) {
        try {
            cout << "Įveskite 1 jei norite, kad duomenys būtų išvesti į ekraną, arba 2 jei norite, kad būtų įrašyti į failą: ";
            cin >> choice;
            if(cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Netinkama įvestis, įveskite skaičių 1 arba 2.");
            }
            if (choice != 1 && choice != 2) {
                throw runtime_error("Netinkama įvestis, įveskite skaičių 1 arba 2.");
            }

            if (choice == 1){
                cout << "\n" << left << setw(15) << "Pavardė" << setw(15) << " Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
                cout << "-------------------------------------------------------" << endl;
                for (int i = 0; i < m; i++) {
                double finalGrade = calculateFinalGrade(students[i], Median);
                cout << setw(15) << students[i].lastName << setw(15) << students[i].firstName << fixed << setprecision(2) << finalGrade << endl;
                }
            } else if (choice == 2){
                ofstream fout("rezultatai.txt");
                if (!fout) {
                    throw runtime_error("Nepavyko įrašyti į 'rezultatai.txt'");
                }
                fout << left << setw(15) << "Pavardė" << setw(15) << " Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
                fout << "-------------------------------------------------------" << endl;
                for (int i = 0; i < m; i++) {
                    double finalGrade = calculateFinalGrade(students[i], Median);
                    fout << setw(15) << students[i].lastName << setw(15) << students[i].firstName << fixed << setprecision(2) << finalGrade << endl;
                }
            }
            break;
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    }
}
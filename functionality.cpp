#include <iostream>
#include <iomanip>
#include <fstream>
#include "functionality.h"

using namespace std;

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
            if (cin.fail() || cin.peek() != '\n' || (result < 1 && result != -1) || result > 10) { // patikrina ar ivestis yra sveikas skaicius nuo 1 iki 10 arba -1
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Netinkama įvestis, įveskite sveiką skaičių nuo 1 iki 10 arba -1 jei baigėte."); 
            }
            return result;
        } catch (const runtime_error& e) {
            cerr << e.what() << '\n';
        }
    }
}

void testFiles(const vector<string>& filenames) {
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

double generateFile(int n) {
    auto start = chrono::high_resolution_clock::now();
    ofstream fout("studentai" + to_string(n) + ".txt");
    if (!fout) {
        cerr << "Nepavyko sukurti failo 'studentai" << n << ".txt'\n";
        return -1.0;
    }

    fout << left << setw(16) << "Vardas" << setw(16) << "Pavarde";
    for (int i = 1; i <= 15; i++) {
        fout << setw(5) << "ND" + to_string(i);
    }
    fout << setw(5) << "Egz." << endl;

    for (int i = 1; i <= n; i++) {
        fout << setw(16) << "Vardas" + to_string(i) << setw(16) << "Pavarde" + to_string(i);
        for (int j = 0; j < 15; j++) {
            fout << setw(5) << generateGrade();
        }
        fout << setw(5) << generateGrade() << endl;
    }
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration<double>(end - start).count();
}

void outputToTerminal(const vector<Student>& studentsLow, const vector<Student>& studentsHigh, bool Median){
    cout <<"\nNuskriaustukai: \n\n";
    cout << left << setw(15) << "Pavardė" << setw(15) << " Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
    cout << "-------------------------------------------------------" << endl;
    for (const auto& student : studentsLow) {
        double finalGrade = calculateFinalGrade(student, Median);
        cout << setw(15) << student.lastName << setw(15) << student.firstName << fixed << setprecision(2) << finalGrade << endl;
    }
    cout <<"\nKietiakai: \n\n";
    cout << left << setw(15) << "Pavardė" << setw(15) << " Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
    cout << "-------------------------------------------------------" << endl;
    for (const auto& student : studentsHigh) {
        double finalGrade = calculateFinalGrade(student, Median);
        cout << setw(15) << student.lastName << setw(15) << student.firstName << fixed << setprecision(2) << finalGrade << endl;
    }
}

void outputToFile(const vector<Student>& students, size_t m, bool Median, const string& filename){
    ofstream fout(filename);
    fout << left << setw(15) << "Pavardė" << setw(15) << " Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
    fout << "-------------------------------------------------------" << endl;
    for (int i = 0; i < m; i++) {
        double finalGrade = calculateFinalGrade(students[i], Median);
        fout << setw(15) << students[i].lastName << setw(15) << students[i].firstName << fixed << setprecision(2) << finalGrade << endl;
    }
    fout.close();
}
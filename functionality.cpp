#include <iostream>
#include <iomanip>
#include <fstream>
#include "functionality.h"

using namespace std;

int getContainerTypeFromUser() {
    int containerType;

    cout << "\nPasirinkite konteinerio tipą: \n";
    cout << "1 - Vector\n";
    cout << "2 - Deque\n";
    cout << "3 - List\n";
    cout << "\nPasirinkite: ";
    cin >> containerType;

    while (containerType < 1 || containerType > 3) {
        cout << "Netinkama įvestis, įveskite skaičių tarp 1 ir 3. \n";
        cin >> containerType;
    }

    return containerType;
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

void generateFile(int n) {
    auto start = std::chrono::high_resolution_clock::now(); 

    ofstream fout("studentai" + to_string(n) + ".txt");
    if (!fout) {
        cerr << "Nepavyko sukurti failo 'studentai" << n << ".txt'\n";
        return;
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

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start; 

    cout << "Failas 'studentai" << n << ".txt' sukurtas per " << diff.count() << " sekundes.\n";
}

void outputToTerminal(const vector<Student>& studentsLow, const vector<Student>& studentsHigh, bool Median){
    cout <<"\nNuskriaustukai: \n\n";
    cout << left << setw(15) << "Pavardė" << setw(15) << " Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
    cout << "-------------------------------------------------------" << endl;
    for (const auto& student : studentsLow) {
        double finalGrade = student.calculateFinalGrade(Median);
        cout << student << fixed << setprecision(2) << finalGrade << endl;
    }
    cout <<"\nKietiakai: \n\n";
    cout << left << setw(15) << "Pavardė" << setw(15) << " Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
    cout << "-------------------------------------------------------" << endl;
    for (const auto& student : studentsHigh) {
        double finalGrade = student.calculateFinalGrade(Median);
        cout << student << fixed << setprecision(2) << finalGrade << endl;
    }
}

template <typename Container>
void outputToFile(const Container& students, size_t m, bool Median, const std::string& filename) {
    ofstream fout(filename);
    fout << left << setw(15) << "Pavardė" << setw(15) << " Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
    fout << "-------------------------------------------------------" << endl;
    for (const auto& student : students) {
        double finalGrade = student.calculateFinalGrade(Median);
        fout << student << fixed << setprecision(2) << finalGrade << endl;
    }
    fout.close();
}

template void outputToFile<std::vector<Student>>(const std::vector<Student>&, size_t, bool, const std::string&);
template void outputToFile<std::deque<Student>>(const std::deque<Student>&, size_t, bool, const std::string&);
template void outputToFile<std::list<Student>>(const std::list<Student>&, size_t, bool, const std::string&);
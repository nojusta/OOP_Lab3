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

void generateFile(int n) {
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
    cout << "Failas 'studentai" << n << ".txt' sukurtas.\n";
}

void output(const vector<Student>& students, size_t m, bool Median){
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
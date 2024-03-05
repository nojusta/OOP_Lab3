#include "input.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <sstream>
#include <ctime>

using namespace std;

bool getMedianPreference() {
    string a;
    while (true) {
        try {
            cout << "Ar norite galutinio balo skaičiavimui naudoti medianą? (1 - taip, 0 - ne): ";
            cin >> a;
            if (a == "0") {
                return false;
            } else if (a == "1") {
                return true;
            } else {
                throw invalid_argument("Neteisinga įvestis. Prašome įvesti 0 arba 1.");
            }
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }
}

void processStudents(vector<Student>& students, bool Median) {
    Student data;
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
                        cout << "Ar norite suvesti dar vieno studento pažymius? (1 - taip, 0 - ne): ";
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
                    vector<string> filenames;
                    filenames.push_back(filename);
                    openFiles(filenames, Median);
                } catch (const runtime_error& e) {
                    cerr << e.what() << '\n';
                } catch (const exception& e) {
                    cerr << "Įvyko klaida: " << e.what() << '\n';
                }
                break;
            }
            case 6: {
                try {
                    int studentCounts[] = {1000, 10000, 100000, 1000000, 10000000};
                    for (int i = 0; i < sizeof(studentCounts)/sizeof(studentCounts[0]); i++) {
                        generateFile(studentCounts[i]);
                    }
                    cout << "\nFailai sukurti sėkmingai." << endl;
                } catch (const exception& e) {
                    cerr << "Įvyko klaida: " << e.what() << '\n';
                }
                break;
            }
            case 7: {
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
                        vector<Student> kietiakai;
                        vector<Student> nuskriaustukai;
                        for (vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                            double finalGrade = calculateFinalGrade(*it, Median);
                            if (finalGrade < 5.0) {
                                nuskriaustukai.push_back(*it);
                            } else {
                                kietiakai.push_back(*it);
                            }
                        }
                        cout << "Įveskite kaip norite išvesti studentus: 1 - į ekraną, 2 - į failus: ";
                        int choice;
                        cin >> choice;
                        if (choice == 1) {
                            outputToTerminal(nuskriaustukai, kietiakai, Median);
                        } else if (choice == 2) {
                            outputToFile(nuskriaustukai, nuskriaustukai.size(), Median, "nuskriaustukai.txt");
                            outputToFile(kietiakai, kietiakai.size(), Median, "kietiakai.txt");
                        }
                    } catch (const exception& e) {
                        cerr << "Įvyko klaida rušiuojant / išvedant studentus \n";
                    }
                } 
                break;
            }
        }
    } while (number != 7);
}

int Menu() {
    int number;
    cout << "\n1 - Suvesti duomenis ranka\n";
    cout << "2 - Generuoti pažymius\n";
    cout << "3 - Generuoti ir pažymius ir studentų vardus, pavardes\n";
    cout << "4 - Skaityti duomenis iš failo\n";
    cout << "5 - Atidaryti testavimo failus\n";
    cout << "6 - Sugeneruoti penkis atsitiktinius studentų sąrašų failus\n";
    cout << "7 - Baigti darbą / Išvedimas\n";
    cout << "\nĮveskite skaičių: ";
    cin >> number;
    if (number < 1 || number > 7) {
        throw runtime_error("Netinkama įvestis, įveskite skaičių tarp 1 ir 7.");
    }
    return number;
}

string getFilenameFromUser() {
    cout << "Įveskite norimo failo pavadinimą (kursiokai.txt, studentai1000.txt, studentai10000.txt, studentai100000.txt, studentai1000000.txt, studentai10000000.txt): \n";
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

void openFiles(const vector<string>& filenames, bool Median) {
    double sumRead = 0.0, sumSort = 0.0, sumOutput = 0.0;
    for (const auto& filename : filenames) { 
        ifstream fin(filename); 
        vector<Student> students;

        // Matuojame laika nuskaitymui
        auto startRead = chrono::high_resolution_clock::now();
        readData(fin, students);
        auto endRead = chrono::high_resolution_clock::now();
        sumRead += chrono::duration<double>(endRead - startRead).count();

        // Matuoja laika rusiavimui 
        auto startSort = chrono::high_resolution_clock::now();
        sortStudents(students, 3);
        vector<Student> kietiakai, nuskriaustukai;
        for (auto& student : students) {
            double finalGrade = calculateFinalGrade(student, Median);
            if (finalGrade < 5.0) {
                nuskriaustukai.push_back(student);
            } else {
                kietiakai.push_back(student);
            }
        }
        auto endSort = chrono::high_resolution_clock::now();
        sumSort += chrono::duration<double>(endSort - startSort).count();

        // Matuojame laika isvedimui i du failus
        auto startOutput = chrono::high_resolution_clock::now();
        outputToFile(nuskriaustukai, nuskriaustukai.size(), Median, "nuskriaustukai.txt");
        outputToFile(kietiakai, kietiakai.size(), Median, "kietiakai.txt");
        auto endOutput = chrono::high_resolution_clock::now();
        sumOutput += chrono::duration<double>(endOutput - startOutput).count();

        fin.clear(); 
        fin.seekg(0); 

        fin.close();
    }

    cout << "\nLaikas sugaištas duomenų nuskaitymui: " << std::fixed << std::setprecision(6) << sumRead << " sekundės" << endl;
    cout << "Laikas sugaištas duomenų rušiavimui: " << std::fixed << std::setprecision(6) << sumSort << " sekundės" << endl;
    cout << "Laikas sugaištas duomenų išvedimui į du failus: " << std::fixed << std::setprecision(6) << sumOutput << " sekundės" << endl;
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

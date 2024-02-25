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

using namespace std;

struct Student {
    string firstName, lastName;
    vector<int> homeworkResults;
    int examResults;
};

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

void sortStudents(vector<Student>& students, int criteria);

void output(const vector<Student>& students, const int & m, bool Median);

int main() {
    srand(time(0));
    Student data;
    bool Median;
    string a;
    while (true) {
        cout << "Ar norite galutinio balo skaiciavimui naudoti mediana? (1 - taip, 0 - ne): ";
        cin >> a;

        if (a == "0") {
            Median = false;
            break;
        } else if (a == "1") {
            Median = true;
            break;
        } else {
            cout << "Neteisinga ivestis. Prasome ivesti 0 arba 1." << endl;
        }
    }
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
                string filename = getFilenameFromUser();
                ifstream fin(filename); 
                if (!fin) {
                    cout << "Nepavyko nuskaityti failo: " << '"' << filename << '"' << endl;
                } else {
                    cout << "\nFailas " << '"' << filename << '"' << " nuskaitytas sekmingai." << endl;
                    readData(fin, students);
                }
                break;
            }
            case 5: {
                string filename = getFilenameFromUser();
                vector<string> filenames;
                filenames.push_back(filename);
                openFiles(filenames);
                break;
            }
            case 6: {
                if (!students.empty()) {
                    cout << "Iveskite kaip norite isrusiuoti studentus: 1 - pagal varda, 2 - pagal pavarde, 3 - pagal galutini bala: ";
                    int criteria;
                    cin >> criteria;
                    sortStudents(students, criteria);
                    output(students, students.size(), Median);
                } 
                break;
            }
            default: {
                cout << "Netinkama ivestis, iveskite skaiciu tarp 1 ir 6.\n";
                break;
            }
        }
    } while (number != 6);
    
    return 0;
}

int Menu() {
    int number;
    cout << "\n1 - Suvesti duomenis ranka\n";
    cout << "2 - Generuoti pazymius\n";
    cout << "3 - Generuoti ir pazymius ir studentu vardus, pavardes\n";
    cout << "4 - Skaityti duomenis is failo\n";
    cout << "5 - Atidaryti testavimo failus\n";
    cout << "6 - Baigti darba / Isvedimas\n";
    cout << "\nIveskite skaiciu: ";
    cin >> number;
    return number;
}

string getFilenameFromUser() {
    cout << "Iveskite norimo failo pavadinima (kursiokai.txt, studentai10000.txt, studentai100000.txt, studentai1000000.txt): \n";
    string filename;
    cin >> filename;
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
            if (ss.good()) { // jei nuskaitymas pavyko, pridedame pazymi i vektoriu
                grades.push_back(grade);
            } else { 
                break; 
            }
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
    for (vector<string>::const_iterator it = filenames.begin(); it != filenames.end(); ++it) { // praeina pro kiekviena string'a vektoriuje
        ifstream fin(*it); 
        if (!fin) {
            cout << "Nepavyko atidaryti failo: " << '"' << *it << '"' << endl;
            continue;
        } else {
            cout << "\nFailas " << '"' << *it << '"' << " atidarytas sekmingai." << endl;
        }
        for (int test = 0; test < numTests; ++test) {
            clock_t start = clock(); // pradedame skaiciuoti laika
            vector<Student> students;
            readData(fin, students);
            clock_t end = clock(); // baigiame skaiciuoti laika
            double sec = double(end - start) / CLOCKS_PER_SEC; // laikas sekundemis
            sum += sec; 
            //cout << "Laikas, praleistas apdorojant duomenis is " << '"' << *it << '"' << " per " << test+1 << " testa: " << sec << " sekundes" << endl;
            fin.clear(); // isvalome failo busena
            fin.seekg(0); // nustatome failo skaitymo pozicija i pradzia
        }
        fin.close();
    }
    double average = sum / (filenames.size() * numTests); // apskaiciuojame vidurki
    cout << "\nKeliu testu laiku vidurkis: " << average << " sekundes" << endl;
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

bool compareByFirstName(const Student& a, const Student& b) {
    return a.firstName < b.firstName;
}

bool compareByLastName(const Student& a, const Student& b) {
    return a.lastName < b.lastName;
}

bool compareByGrade(const Student& a, const Student& b) {
    return calculateFinalGrade(a, false) < calculateFinalGrade(b, false);
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
    do {
        cout << "Iveskite 1 jei norite, kad duomenys butu isvesti i ekrana, arba 2 jei norite, kad butu isvesti i faila: ";
        cin >> choice;
        if (choice == 1){
            cout << "\n" << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
            cout << "-------------------------------------------------------" << endl;
            for (int i = 0; i < m; i++) {
                double finalGrade = calculateFinalGrade(students[i], Median);
                cout << setw(15) << students[i].lastName << setw(15) << students[i].firstName << fixed << setprecision(2) << finalGrade << endl;
            }
        } else if (choice == 2){
            ofstream fout("rezultatai.txt");
            fout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
            fout << "-------------------------------------------------------" << endl;
            for (int i = 0; i < m; i++) {
                double finalGrade = calculateFinalGrade(students[i], Median);
                fout << setw(15) << students[i].lastName << setw(15) << students[i].firstName << fixed << setprecision(2) << finalGrade << endl;
            }
            fout.close();
        } else {
            cout << "Netinkama ivestis, iveskite skaiciu 1 arba 2." << endl;
        } 
    } while (choice != 1 && choice != 2);
}
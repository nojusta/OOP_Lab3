#include <iostream>
#include <vector>
#include <iomanip>
#include <string> 

using namespace std;

struct Student {
    string firstName, lastName;
    vector<int> homeworkResults;
    int examResults;
};

void input(Student& data);

double calculateAverage(const vector<int>& homeworkResults);

int main() {
    Student data;
    input(data);
    cout << "Iveskite studentu skaiciu: " ; 
    int m;
    cin >> m;
    vector<Student> students(m);
    for (int i = 0; i < m; i++) {
        input(students[i]);
    }
    return 0;
}

void input(Student& data){
    cout << "Iveskite studento varda: ";
    cin >> data.firstName;
    cout << "Iveskite studento pavarde: ";
    cin >> data.lastName;
    cout << "Iveskite studento namu darbu kieki (n): ";
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Iveskite " << i + 1 << "-ajo namu darbo rezultata: ";
        int grade;
        cin >> grade;
        data.homeworkResults.push_back(grade);
    }
    cout << "Iveskite studento egzamino rezultata: ";
    cin >> data.examResults;
    
}

double calculateAverage(const vector<int>& homeworkResults) {
    double sum = 0;
    for (int i = 0; i < homeworkResults.size(); i++) {
        sum += homeworkResults[i];
    }
    return sum / homeworkResults.size();
}
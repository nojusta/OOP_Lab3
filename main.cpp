#include <iostream>
#include <vector>

using namespace std;

struct Student {
    string firstName, lastName;
    vector<int> homeworkResults;
    int examResults;
};

void input();

int main() {
    return 0;
}

void input(){
    Student data;
    cout << "Iveskite studento varda: ";
    cin >> data.firstName;
    cout << "Iveskite studento pavarde: ";
    cin >> data.lastName;
    cout << "Iveskite studento namu darbu kieki (n): ";
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Iveskite " << i + 1 << "-aji namu darba: ";
        int grade;
        cin >> grade;
        data.homeworkResults.push_back(grade);
    }
    cout << "Iveskite studento egzamino rezultata: ";
    cin >> data.examResults;
    
}
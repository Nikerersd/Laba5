#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> students;
vector<int> suspicious_list;

void addStudents(int number) {
    if (number > 0) {
        students.reserve(students.size() + number);
        for (int i = 0; i < number; ++i)
            students.push_back("clever student");
        cout << "Welcome " << number << " clever students!" << endl;
    } else {
        number = -number;
        if (number > students.size()) {
            cout << "Incorrect" << endl;
            return;
        }
        students.resize(students.size() - number);
        cout << "Goodbye " << number << " clever students!" << endl;
    }
}

void markSuspicious(int number_student) {
    if (number_student < 1 || number_student > students.size()) {
        cout << "Incorrect" << endl;
        return;
    }
    suspicious_list.push_back(number_student);
    cout << "The suspected student " << number_student << endl;
}

void markImmortal(int number_student) {
    if (number_student < 1 || number_student > students.size()) {
        cout << "Incorrect" << endl;
        return;
    }
    auto it = find(suspicious_list.begin(), suspicious_list.end(), number_student);
    if (it != suspicious_list.end()) {
        suspicious_list.erase(it);
        cout << "Student " << number_student << " is immortal!" << endl;
    } else {
        cout << "Incorrect" << endl;
    }
}

void printTopList() {
    if (suspicious_list.empty()) {
        cout << "List of students for expulsion is empty" << endl;
        return;
    }
    cout << "List of students for expulsion:";
    for (int student_number : suspicious_list) {
        cout << " Student " << student_number;
    }
    cout << endl;
}

void printSuspiciousCount() {
    cout << "List of students for expulsion consists of " << suspicious_list.size() << " students" << endl;
}

int main() {
    string command;
    int parameter;

    while (true) {
        cin >> command;
        if (command == "NEW_STUDENTS" || command == "SUSPICIOUS" || command == "IMMORTAL") {
            cin >> parameter;
        }

        if (command == "NEW_STUDENTS") {
            addStudents(parameter);
        } else if (command == "SUSPICIOUS") {
            markSuspicious(parameter);
        } else if (command == "IMMORTAL") {
            markImmortal(parameter);
        } else if (command == "TOP-LIST") {
            printTopList();
        } else if (command == "SCOUNT") {
            printSuspiciousCount();
        } else if (command == "exit") {
            break;
        } else {
            cout << "Incorrect" << endl;
        }
    }

    return 0;
}

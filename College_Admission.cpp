#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

class Student {
public:
    string studentID, name, gender, department;
    int age;
    double sscGPA, hscGPA;

    void registerStudent();
    bool isEligible();
    void allocateDepartment();
    void displayInfo();
};

void Student::registerStudent() {
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Gender: ";
    cin >> gender;
    cout << "Enter SSC GPA: ";
    cin >> sscGPA;
    cout << "Enter HSC GPA: ";
    cin >> hscGPA;
    cout << "Enter Student ID: ";
    cin >> studentID;

    if (isEligible()) {
        allocateDepartment();
        cout << "Student registered successfully!\n";
    } else {
        cout << "Sorry, not eligible for admission.\n";
        department = "None";
    }
}

bool Student::isEligible() {
    return (sscGPA + hscGPA) >= 8.0;
}

void Student::allocateDepartment() {
    int choice;
    cout << "Choose Department:\n1. CSE\n2. EEE\n3. BBA\nEnter choice: ";
    cin >> choice;
    switch (choice) {
        case 1: department = "CSE"; break;
        case 2: department = "EEE"; break;
        case 3: department = "BBA"; break;
        default: department = "Undecided"; break;
    }
}

void Student::displayInfo() {
    cout << left << setw(10) << studentID << setw(20) << name << setw(5) << age
         << setw(10) << gender << setw(10) << sscGPA << setw(10) << hscGPA
         << setw(10) << department << endl;
}

class AdmissionSystem {
    vector<Student> students;

public:
    void newAdmission();
    void viewAllStudents();
    void saveToFile();
    void loadFromFile();
};

void AdmissionSystem::newAdmission() {
    Student s;
    s.registerStudent();
    if (s.isEligible())
        students.push_back(s);
}

void AdmissionSystem::viewAllStudents() {
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(5) << "Age"
         << setw(10) << "Gender" << setw(10) << "SSC GPA" << setw(10) << "HSC GPA"
         << setw(10) << "Dept" << endl;
    for (auto &s : students) {
        s.displayInfo();
    }
}

void AdmissionSystem::saveToFile() {
    ofstream out("students.txt");
    for (auto &s : students) {
        out << s.studentID << " " << s.name << " " << s.age << " " << s.gender << " "
            << s.sscGPA << " " << s.hscGPA << " " << s.department << endl;
    }
    out.close();
    cout << "Data saved to students.txt\n";
}

void AdmissionSystem::loadFromFile() {
    ifstream in("students.txt");
    Student s;
    students.clear();
    while (in >> s.studentID >> ws && getline(in, s.name, ' ') && in >> s.age >> s.gender >> s.sscGPA >> s.hscGPA >> s.department) {
        students.push_back(s);
    }
    in.close();
    cout << "Data loaded from students.txt\n";
}

int main() {
    AdmissionSystem system;
    int choice;
    system.loadFromFile();

    do {
        cout << "\n==== College Admission System ====\n";
        cout << "1. New Admission\n2. View All Students\n3. Save to File\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: system.newAdmission(); break;
            case 2: system.viewAllStudents(); break;
            case 3: system.saveToFile(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}

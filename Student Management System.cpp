#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

class Student {
public:
    int roll;
    string name;
    string course;
    float marks;


    void input() {
        cout << "Enter Roll Number: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Course: ";
        getline(cin, course);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() const {
        cout << left << setw(10) << roll
             << setw(20) << name
             << setw(15) << course
             << setw(10) << marks << endl;
    }

    string toCSV() const {
        ostringstream oss;
        oss << roll << "," << name << "," << course << "," << marks;
        return oss.str();
    }

    static Student fromCSV(const string& line) {
        Student s;
        stringstream ss(line);
        string token;

        getline(ss, token, ',');
        stringstream(token) >> s.roll;

        getline(ss, s.name, ',');

        getline(ss, s.course, ',');

        getline(ss, token, ',');
        stringstream(token) >> s.marks;

        return s;
    }
};

// Function to add student
void addStudent() {
    ofstream out("students.txt", ios::app);
    if (!out) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    Student s;
    s.input();
    out << s.toCSV() << "\n";
    out.close();

    cout << "? Student added successfully.\n";
}

// Function to display all students
void displayAll() {
    ifstream in("students.txt");
    if (!in) {
        cerr << "? File not found.\n";
        return;
    }

    cout << "\n?? All Students:\n";
    cout << left << setw(10) << "Roll"
         << setw(20) << "Name"
         << setw(15) << "Course"
         << setw(10) << "Marks" << endl;
    cout << "-------------------------------------------------------------\n";

    string line;
    int count = 0;
    while (getline(in, line)) {
        if (line.empty()) continue;
        Student s = Student::fromCSV(line);
        s.display();
        count++;
    }

    if (count == 0) {
        cout << "No student records found.\n";
    }

    in.close();
}

// Search student by roll number
void searchStudent() {
    int target;
    cout << "Enter roll number to search: ";
    cin >> target;

    ifstream in("students.txt");
    if (!in) {
        cerr << "? File not found.\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(in, line)) {
        if (line.empty()) continue;

        Student s = Student::fromCSV(line);
        if (s.roll == target) {
            cout << "\n?? Student Found:\n";
            cout << left << setw(10) << "Roll"
                 << setw(20) << "Name"
                 << setw(15) << "Course"
                 << setw(10) << "Marks" << endl;
            cout << "-------------------------------------------------------------\n";
            s.display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student with roll number " << target << " not found.\n";
    }

    in.close();
}

int main() {
    int choice;
    do {
        cout << "\n========== Student Management System ==========\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by Roll Number\n";
        cout << "4. Exit\n";
        cout << "===============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: cout << "?? Exiting program. Goodbye!\n"; break;
            default: cout << "? Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}


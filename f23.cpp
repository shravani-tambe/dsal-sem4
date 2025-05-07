/*student management system using index sequential files*/ 

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
using namespace std;

struct Student {
    int rollNumber;
    char name[50];
    char division;
    char address[100];
};

void addStudent() {
    ofstream outFile("students.txt", ios::app);
    Student student;

    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cin.ignore();

    cout << "Enter Name: ";
    cin.getline(student.name, 50);

    cout << "Enter Division: ";
    cin >> student.division;
    cin.ignore();

    cout << "Enter Address: ";
    cin.getline(student.address, 100);

    outFile << student.rollNumber << ","
            << student.name << ","
            << student.division << ","
            << student.address << "\n";

    outFile.close();
    cout << "Student added successfully.\n";
}

void deleteStudent(int rollNumber) {
    ifstream inFile("students.txt");
    ofstream outFile("temp.txt");

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string rollStr;
        getline(ss, rollStr, ',');
        if (stoi(rollStr) != rollNumber) {
            outFile << line << "\n";
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Student record deleted successfully.\n";
    else
        cout << "Student record not found.\n";
}

void displayStudent(int rollNumber) {
    ifstream inFile("students.txt");
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string rollStr, name, div, addr;

        getline(ss, rollStr, ',');
        getline(ss, name, ',');
        getline(ss, div, ',');
        getline(ss, addr);

        if (stoi(rollStr) == rollNumber) {
            cout << "\n--- Student Details ---\n";
            cout << "Roll Number: " << rollStr << "\n";
            cout << "Name: " << name << "\n";
            cout << "Division: " << div << "\n";
            cout << "Address: " << addr << "\n";
            found = true;
            break;
        }
    }

    inFile.close();
    if (!found)
        cout << "Student record not found.\n";
}

int main() {
    int choice, rollNumber;

    do {
        cout << "\n----- Student Information System -----\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Display Student\n";
        cout << "4. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2:
                cout << "Enter Roll Number to delete: ";
                cin >> rollNumber;
                deleteStudent(rollNumber);
                break;
            case 3:
                cout << "Enter Roll Number to display: ";
                cin >> rollNumber;
                displayStudent(rollNumber);
                break;
            case 4:
                cout << "Thanks for using the program!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}

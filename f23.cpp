/*student management system using index sequential files*/ 

##include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct Student {
    int rollNumber;
    char name[50];
    char division;
    char address[100];
};

struct IndexEntry {
    int rollNumber;
    long position;
};

void writeIndex(int rollNumber, long pos) {
    ofstream idxFile("index.dat", ios::binary | ios::app);
    idxFile.write(reinterpret_cast<char*>(&rollNumber), sizeof(rollNumber));
    idxFile.write(reinterpret_cast<char*>(&pos), sizeof(pos));
    idxFile.close();
}

vector<IndexEntry> loadIndex() {
    vector<IndexEntry> index;
    ifstream idxFile("index.dat", ios::binary);
    IndexEntry entry;
    while (idxFile.read(reinterpret_cast<char*>(&entry.rollNumber), sizeof(entry.rollNumber))) {
        idxFile.read(reinterpret_cast<char*>(&entry.position), sizeof(entry.position));
        index.push_back(entry);
    }
    idxFile.close();
    sort(index.begin(), index.end(), [](IndexEntry a, IndexEntry b) {
        return a.rollNumber < b.rollNumber;
    });
    return index;
}

void addStudent() {
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

    ofstream outFile("students.dat", ios::binary | ios::app);
    long pos = outFile.tellp();
    outFile.write(reinterpret_cast<char*>(&student), sizeof(Student));
    outFile.close();

    writeIndex(student.rollNumber, pos);
    cout << "Student added successfully.\n";
}

void displayStudent(int rollNumber) {
    vector<IndexEntry> index = loadIndex();
    auto it = find_if(index.begin(), index.end(), [rollNumber](IndexEntry e) {
        return e.rollNumber == rollNumber;
    });

    if (it != index.end()) {
        ifstream inFile("students.dat", ios::binary);
        inFile.seekg(it->position);
        Student student;
        inFile.read(reinterpret_cast<char*>(&student), sizeof(Student));
        inFile.close();

        cout << "\n--- Student Details ---\n";
        cout << "Roll Number: " << student.rollNumber << "\n";
        cout << "Name: " << student.name << "\n";
        cout << "Division: " << student.division << "\n";
        cout << "Address: " << student.address << "\n";
    } else {
        cout << "Student record not found.\n";
    }
}

void deleteStudent(int rollNumber) {
    vector<IndexEntry> index = loadIndex();
    bool found = false;

    ofstream tempData("temp.dat", ios::binary);
    ofstream tempIndex("temp_idx.dat", ios::binary);
    ifstream dataFile("students.dat", ios::binary);

    Student student;
    for (const auto& entry : index) {
        dataFile.seekg(entry.position);
        dataFile.read(reinterpret_cast<char*>(&student), sizeof(Student));
        if (student.rollNumber != rollNumber) {
            long newPos = tempData.tellp();
            tempData.write(reinterpret_cast<char*>(&student), sizeof(Student));
            tempIndex.write(reinterpret_cast<const char*>(&student.rollNumber), sizeof(student.rollNumber));
            tempIndex.write(reinterpret_cast<const char*>(&newPos), sizeof(newPos));
        } else {
            found = true;
        }
    }

    dataFile.close();
    tempData.close();
    tempIndex.close();

    remove("students.dat");
    remove("index.dat");
    rename("temp.dat", "students.dat");
    rename("temp_idx.dat", "index.dat");

    if (found)
        cout << "Student record deleted successfully.\n";
    else
        cout << "Student record not found.\n";
}

int main() {
    int choice, rollNumber;
    do {
        cout << "\n----- Student Management System (ISF) -----\n";
        cout << "1. Add Student\n";
        cout << "2. Display Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2:
                cout << "Enter Roll Number to display: ";
                cin >> rollNumber;
                displayStudent(rollNumber);
                break;
            case 3:
                cout << "Enter Roll Number to delete: ";
                cin >> rollNumber;
                deleteStudent(rollNumber);
                break;
            case 4:
                cout << "Exiting system...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
/*exp f24 : employee management system using index sequential file*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Employee {
    long code;
    char name[50];
    char designation[30];
    int exp;
    int age;
};

struct IndexEntry {
    long code;
    long position;
};

void writeEmployee(Employee &e) {
    ofstream empFile("employee.dat", ios::binary | ios::app);
    long pos = empFile.tellp();
    empFile.write(reinterpret_cast<char*>(&e), sizeof(Employee));
    empFile.close();

    ofstream idxFile("index.dat", ios::binary | ios::app);
    idxFile.write(reinterpret_cast<char*>(&e.code), sizeof(e.code));
    idxFile.write(reinterpret_cast<char*>(&pos), sizeof(pos));
    idxFile.close();
}

vector<IndexEntry> loadIndex() {
    vector<IndexEntry> index;
    ifstream idxFile("index.dat", ios::binary);
    IndexEntry entry;
    while (idxFile.read(reinterpret_cast<char*>(&entry.code), sizeof(entry.code))) {
        idxFile.read(reinterpret_cast<char*>(&entry.position), sizeof(entry.position));
        index.push_back(entry);
    }
    idxFile.close();
    sort(index.begin(), index.end(), [](IndexEntry a, IndexEntry b) {
        return a.code < b.code;
    });
    return index;
}

void searchEmployee(long code) {
    vector<IndexEntry> index = loadIndex();
    auto it = find_if(index.begin(), index.end(), [code](IndexEntry e) {
        return e.code == code;
    });

    if (it != index.end()) {
        ifstream empFile("employee.dat", ios::binary);
        empFile.seekg(it->position);
        Employee e;
        empFile.read(reinterpret_cast<char*>(&e), sizeof(Employee));
        empFile.close();

        cout << "Employee found:\n";
        cout << "Code: " << e.code << "\n";
        cout << "Name: " << e.name << "\n";
        cout << "Designation: " << e.designation << "\n";
        cout << "Experience: " << e.exp << "\n";
        cout << "Age: " << e.age << "\n";
    } else {
        cout << "Employee not found.\n";
    }
}

void insertEmployee() {
    Employee e;
    cout << "Enter Code: "; cin >> e.code;
    cin.ignore();
    cout << "Enter Name: "; cin.getline(e.name, 50);
    cout << "Enter Designation: "; cin.getline(e.designation, 30);
    cout << "Enter Experience: "; cin >> e.exp;
    cout << "Enter Age: "; cin >> e.age;

    writeEmployee(e);
    cout << "Employee inserted successfully.\n";
}

void menu() {
    while (true) {
        cout << "\nEmployee Management System\n";
        cout << "1. Insert Employee\n";
        cout << "2. Search Employee\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                insertEmployee();
                break;
            case 2:
                long code;
                cout << "Enter Employee Code to Search: ";
                cin >> code;
                searchEmployee(code);
                break;
            case 3:
                cout << "Exiting...\n";
                return;
            default:
                cout << "Invalid option.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}
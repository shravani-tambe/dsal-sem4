/*exp f24 : employee management system using index sequential file*/

#include <iostream>
#include <string>
using namespace std;

const int MAX_EMPLOYEES = 20;

struct employee {
    string name;
    long int code;
    string designation;
    int exp;
    int age;
};

employee emp[MAX_EMPLOYEES];
int num = 0;

void insert() {
    if (num < MAX_EMPLOYEES) {
        int i = num;
        num++;

        cout << "Enter the information of the Employee.\n";
        cin.ignore(); 

        cout << "Name: ";
        getline(cin, emp[i].name);

        cout << "Employee ID: ";
        cin >> emp[i].code;
        cin.ignore();

        cout << "Designation: ";
        getline(cin, emp[i].designation);

        cout << "Experience: ";
        cin >> emp[i].exp;

        cout << "Age: ";
        cin >> emp[i].age;

        cout << "Employee added successfully!\n";
    } else {
        cout << "Employee list is full.\n";
    }
}

void deleteIndex(int i) {
    for (int j = i; j < num - 1; j++) {
        emp[j] = emp[j + 1];
    }
}

void deleteRecord() {
    cout << "Enter the Employee ID to delete: ";
    long int code;
    cin >> code;

    bool found = false;
    for (int i = 0; i < num; i++) {
        if (emp[i].code == code) {
            deleteIndex(i);
            num--;
            found = true;
            cout << "Record deleted successfully.\n";
            break;
        }
    }
    if (!found) {
        cout << "Employee ID not found.\n";
    }
}

void searchRecord() {
    cout << "Enter the Employee ID to search: ";
    long int code;
    cin >> code;

    bool found = false;
    for (int i = 0; i < num; i++) {
        if (emp[i].code == code) {
            cout << "Name: " << emp[i].name << "\n";
            cout << "Employee ID: " << emp[i].code << "\n";
            cout << "Designation: " << emp[i].designation << "\n";
            cout << "Experience: " << emp[i].exp << "\n";
            cout << "Age: " << emp[i].age << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Employee ID not found.\n";
    }
}

void showMenu() {
    cout << "\n------------------------- Employee Management System -------------------------\n";
    cout << "Available Options:\n";
    cout << "1. Insert New Entry\n";
    cout << "2. Delete Entry\n";
    cout << "3. Search a Record\n";
    cout << "4. Exit\n";
    cout << "Choose an option (1-4): ";
}

int main() {
    while (true) {
        showMenu();
        int option;
        cin >> option;

        switch (option) {
            case 1: insert(); break;
            case 2: deleteRecord(); break;
            case 3: searchRecord(); break;
            case 4:
                cout << "Exiting Employee Management System.\n";
                return 0;
            default:
                cout << "Invalid option. Please enter a number between 1 and 4.\n";
        }
    }

    return 0;
}

/*
Implement all the functions of a dictionary (ADT) using hashing and handle collisions using chaining with / without replacement.
Data: Set of (key, value) pairs, Keys are mapped to values, Keys must be comparable, Keys must be unique.
Standard Operations: Insert(key, value), Find(key), Delete(key)
*/

#include <iostream>
#include <list>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

struct Pair {
    string key;
    string value;
};

class Dictionary {
    list<Pair> table[TABLE_SIZE];

    int hashFunction(const string& key) {
        int hash = 0;
        for (char ch : key)
            hash = (hash * 31 + ch) % TABLE_SIZE;
        return hash;
    }

public:
    void insert(const string& key, const string& value) {
        int index = hashFunction(key);
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                pair.value = value;
                return;
            }
        }
        table[index].push_back({key, value});
    }

    string find(const string& key) {
        int index = hashFunction(key);
        for (auto& pair : table[index]) {
            if (pair.key == key)
                return pair.value;
        }
        return "Key not found";
    }

    void remove(const string& key) {
        int index = hashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                table[index].erase(it);
                return;
            }
        }
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "[" << i << "]: ";
            for (auto& pair : table[i]) {
                cout << "(" << pair.key << ", " << pair.value << ") ";
            }
            cout << "\n";
        }
    }
};

int main() {
    Dictionary dict;
    int choice;
    string key, value;

    cout << "\n1. Insert\n2. Find\n3. Delete\n4. Display\n5. Exit\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    while (choice != 5) {
        switch (choice) {
            case 1:
                cout << "Enter key: ";
                getline(cin, key);
                cout << "Enter value: ";
                getline(cin, value);
                dict.insert(key, value);
                break;
            case 2:
                cout << "Enter key to find: ";
                getline(cin, key);
                cout << "Value: " << dict.find(key) << "\n";
                break;
            case 3:
                cout << "Enter key to delete: ";
                getline(cin, key);
                dict.remove(key);
                break;
            case 4:
                dict.display();
                break;
            default:
                cout << "Invalid choice\n";
        }

        cout << "\n1. Insert\n2. Find\n3. Delete\n4. Display\n5. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore();
    }

    return 0;
}

/*book consists of chapters, chapters of sections and sections of subsections. construct a tree and print the nodes. find tc nd sc*/

#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

struct node {
    char label[30];
    int ch_count;
    int sb_count;
    node* child[30];

    node() {
        ch_count = 0;
        sb_count = 0;
        for (int i = 0; i < 30; i++) {
            child[i] = NULL;
        }
    }
};

class BST {
    node* root;

public:
    BST() {
        root = NULL;
    }

    void create_tree();
    void display();

private:
    void display_helper(node* r1);
};

void BST::create_tree() {
    int tchapters;
    root = new node();
    cout << "Enter Name of Book: ";
    cin >> root->label;

    cout << "Enter number of Chapters in Book: ";
    cin >> tchapters;
    root->ch_count = tchapters;

    for (int i = 0; i < tchapters; i++) {
        root->child[i] = new node();
        cout << "\nEnter Chapter " << i + 1 << " Name: ";
        cin >> root->child[i]->label;

        cout << "Enter number of Sections in Chapter " << root->child[i]->label << ": ";
        cin >> root->child[i]->ch_count;

        for (int j = 0; j < root->child[i]->ch_count; j++) {
            root->child[i]->child[j] = new node();
            cout << "Enter Section " << j + 1 << " Name: ";
            cin >> root->child[i]->child[j]->label;

            cout << "Enter number of Subsections in Section " << root->child[i]->child[j]->label << ": ";
            cin >> root->child[i]->child[j]->sb_count;

            for (int k = 0; k < root->child[i]->child[j]->sb_count; k++) {
                root->child[i]->child[j]->child[k] = new node();
                cout << "Enter Subsection " << k + 1 << " Name: ";
                cin >> root->child[i]->child[j]->child[k]->label;
            }
        }
    }
}

void BST::display() {
    if (root == NULL) {
        cout << "\nBook tree is empty. Create it first.\n";
        return;
    }

    cout << "\n----- BOOK STRUCTURE -----\n";
    cout << "BOOK TITLE: " << root->label << endl;
    display_helper(root);
}

void BST::display_helper(node* r1) {
    for (int i = 0; i < r1->ch_count; i++) {
        cout << "\n  Chapter " << i + 1 << ": " << r1->child[i]->label;

        for (int j = 0; j < r1->child[i]->ch_count; j++) {
            cout << "\n    Section " << i + 1 << "." << j + 1 << ": " << r1->child[i]->child[j]->label;

            for (int k = 0; k < r1->child[i]->child[j]->sb_count; k++) {
                cout << "\n      Subsection " << i + 1 << "." << j + 1 << "." << k + 1 << ": " << r1->child[i]->child[j]->child[k]->label;
            }
        }
    }
}

int main() {
    int choice;
    BST bst;

    while (true) {
        cout << "\n---------------------------" << endl;
        cout << " Book Tree Creation System " << endl;
        cout << "---------------------------" << endl;
        cout << "1. Create Tree" << endl;
        cout << "2. Display Tree" << endl;
        cout << "3. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bst.create_tree();
            break;
        case 2:
            bst.display();
            break;
        case 3:
            cout << "Exiting... Goodbye!\n";
            exit(0);
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

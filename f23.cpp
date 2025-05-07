/*student management system using index sequential files*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUD_FILE "STUD.DAT"

typedef struct {
    int roll;
    char name[30];
    char division;
    char address[50];
} Student;

void createFile() {
    FILE *fp = fopen(STUD_FILE, "wb");
    if (!fp) {
        perror("Cannot create file");
        return;
    }
    fclose(fp);
    printf("File created: %s\n", STUD_FILE);
}

void addStudent() {
    Student s;
    FILE *fp = fopen(STUD_FILE, "ab");
    if (!fp) { perror("Open"); return; }

    printf("Roll No    : "); scanf("%d", &s.roll);
    printf("Name       : "); scanf(" %[^\n]", s.name);
    printf("Division   : "); scanf(" %c", &s.division);
    printf("Address    : "); scanf(" %[^\n]", s.address);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Record added.\n");
}

void deleteStudent() {
    int key, found = 0;
    printf("Enter Roll No to delete: "); scanf("%d", &key);

    FILE *fp = fopen(STUD_FILE, "rb");
    FILE *tmp = fopen("TMP.DAT", "wb");
    if (!fp || !tmp) { perror("Open"); return; }

    Student s;
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == key) {
            found = 1;
        } else {
            fwrite(&s, sizeof(s), 1, tmp);
        }
    }
    fclose(fp); fclose(tmp);

    if (found) {
        remove(STUD_FILE);
        rename("TMP.DAT", STUD_FILE);
        printf("Deleted roll %d.\n", key);
    } else {
        remove("TMP.DAT");
        printf("Roll %d not found.\n", key);
    }
}

void displayStudent() {
    int key, found = 0;
    printf("Enter Roll No to display: "); scanf("%d", &key);

    FILE *fp = fopen(STUD_FILE, "rb");
    if (!fp) { perror("Open"); return; }

    Student s;
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == key) {
            printf("\nRoll     : %d\n", s.roll);
            printf("Name     : %s\n", s.name);
            printf("Division : %c\n", s.division);
            printf("Address  : %s\n", s.address);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("Roll %d not found.\n", key);
}

int main() {
    int choice;
    do {
        printf("\n=== Student Sequential File ===\n");
        printf("1. Create File\n");
        printf("2. Add Record\n");
        printf("3. Delete Record\n");
        printf("4. Display Record\n");
        printf("5. Exit\n");
        printf("Choice: "); scanf("%d", &choice);
        switch (choice) {
            case 1: createFile();    break;
            case 2: addStudent();    break;
            case 3: deleteStudent(); break;
            case 4: displayStudent();break;
            case 5: printf("Bye!\n"); break;
            default: printf("Invalid.\n");
        }
    } while (choice != 5);
    return 0;
}

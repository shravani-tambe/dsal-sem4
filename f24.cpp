/* index sequential file organization for employee management system */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMP_FILE   "EMP.DAT"
#define INDEX_FILE "INDEX.DAT"

typedef struct {
    int id;
    char name[30];
    char desig[20];
    float salary;
} Employee;

typedef struct {
    int id;
    long offset;
} IndexEntry;

void buildIndex() {
    FILE *df = fopen(EMP_FILE, "rb");
    FILE *ix = fopen(INDEX_FILE, "wb");
    if (!df || !ix) { perror("Open"); return; }

    Employee e;
    long pos;
    while ((pos = ftell(df)), fread(&e, sizeof(e), 1, df) == 1) {
        IndexEntry ie = { e.id, pos };
        fwrite(&ie, sizeof(ie), 1, ix);
    }
    fclose(df); fclose(ix);

    // sort index
    ix = fopen(INDEX_FILE, "rb+");
    fseek(ix, 0, SEEK_END);
    int n = ftell(ix) / sizeof(IndexEntry);
    rewind(ix);
    IndexEntry *arr = malloc(n * sizeof(IndexEntry));
    fread(arr, sizeof(IndexEntry), n, ix);
    for (int i = 0; i < n-1; ++i)
      for (int j = 0; j < n-1-i; ++j)
        if (arr[j].id > arr[j+1].id) {
          IndexEntry tmp = arr[j];
          arr[j] = arr[j+1];
          arr[j+1] = tmp;
        }
    rewind(ix);
    fwrite(arr, sizeof(IndexEntry), n, ix);
    free(arr);
    fclose(ix);
}

void addEmployee() {
    Employee e;
    printf("ID        : "); scanf("%d", &e.id);
    printf("Name      : "); scanf(" %[^\n]", e.name);
    printf("Designation: "); scanf(" %[^\n]", e.desig);
    printf("Salary    : "); scanf("%f", &e.salary);

    FILE *df = fopen(EMP_FILE, "ab");
    if (!df) { perror("Open"); return; }
    fwrite(&e, sizeof(e), 1, df);
    fclose(df);

    buildIndex();
    printf("Employee added.\n");
}

void deleteEmployee() {
    int key, found=0;
    printf("Enter ID to delete: "); scanf("%d", &key);

    FILE *df = fopen(EMP_FILE, "rb");
    FILE *tmp = fopen("TMP.DAT", "wb");
    if (!df || !tmp) { perror("Open"); return; }

    Employee e;
    while (fread(&e, sizeof(e), 1, df)) {
        if (e.id == key) found = 1;
        else fwrite(&e, sizeof(e), 1, tmp);
    }
    fclose(df); fclose(tmp);

    if (found) {
        remove(EMP_FILE);
        rename("TMP.DAT", EMP_FILE);
        buildIndex();
        printf("Deleted ID %d.\n", key);
    } else {
        remove("TMP.DAT");
        printf("ID %d not found.\n", key);
    }
}

void displayEmployee() {
    int key;
    printf("Enter ID to display: "); scanf("%d", &key);

    FILE *ix = fopen(INDEX_FILE, "rb");
    if (!ix) {
        printf("Index missing. Rebuilding...\n");
        buildIndex();
        ix = fopen(INDEX_FILE, "rb");
    }

    // load index into memory
    fseek(ix, 0, SEEK_END);
    int n = ftell(ix) / sizeof(IndexEntry);
    rewind(ix);
    IndexEntry *arr = malloc(n * sizeof(IndexEntry));
    fread(arr, sizeof(IndexEntry), n, ix);
    fclose(ix);

    // binary search
    int lo = 0, hi = n - 1, found = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (arr[mid].id == key) {
            FILE *df = fopen(EMP_FILE, "rb");
            fseek(df, arr[mid].offset, SEEK_SET);
            Employee e;
            fread(&e, sizeof(e), 1, df);
            fclose(df);

            printf("\nID        : %d\n", e.id);
            printf("Name      : %s\n", e.name);
            printf("Designation: %s\n", e.desig);
            printf("Salary    : %.2f\n", e.salary);
            found = 1;
            break;
        }
        else if (arr[mid].id < key) lo = mid + 1;
        else hi = mid - 1;
    }
    free(arr);

    if (!found)
        printf("ID %d not found.\n", key);
}

int main() {
    int ch;
    do {
        printf("\n=== Employee Index-Sequential ===\n");
        printf("1. Build Index\n");
        printf("2. Add Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Display Employee\n");
        printf("5. Exit\n");
        printf("Choice: "); scanf("%d", &ch);
        switch (ch) {
            case 1: buildIndex();      break;
            case 2: addEmployee();     break;
            case 3: deleteEmployee();  break;
            case 4: displayEmployee(); break;
            case 5: printf("Done.\n"); break;
            default: printf("Invalid.\n");
        }
    } while (ch != 5);
    return 0;
}

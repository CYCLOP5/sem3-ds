#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define EMPTY -1
#define DELETED -2

int array[SIZE];

void insert();
void delete();
void search();
void hash_table();

int main() {
    int choice;

    for (int i = 0; i < SIZE; i++) {
        array[i] = EMPTY;
    }

    while (1) {
        printf("Select one of the following options:\n");
        printf("1. Insertion\n2. Deletion\n3. Searching\n4. Print table\n5. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insert(); break;
            case 2: delete(); break;
            case 3: search(); break;
            case 4: hash_table(); break;
            case 5: exit(0);
            default: printf("check again.\n");
        }
    }

    return 0;
}

void insert() {
    int key, index, i;

    printf("\nenter key: ");
    scanf("%d", &key);

    index = (key % SIZE + SIZE) % SIZE; 

    for (i = 0; i < SIZE; i++) {
        int probeIndex = (index + i) % SIZE;
        if (array[probeIndex] == key) {
            printf("Key %d already exists at index %d ie duplicate.\n", key, probeIndex);
            return;
        }
    }

    for (i = 0; i < SIZE; i++) {
        int probeIndex = (index + i) % SIZE;
        if (array[probeIndex] == EMPTY || array[probeIndex] == DELETED) {
            array[probeIndex] = key;
            printf("Key %d inserted at index %d.\n", key, probeIndex);
            return;
        }
    }

    printf("Hash table is full.\n");
}

void delete() {
    int key, index, i;

    printf("\nEnter the key to delete: ");
    scanf("%d", &key);

    index = (key % SIZE + SIZE) % SIZE; 

    for (i = 0; i < SIZE; i++) {
        int probeIndex = (index + i) % SIZE;
        if (array[probeIndex] == EMPTY) {
            printf("key %d does not exist in the table.\n", key);
            return;
        } else if (array[probeIndex] == key) {
            array[probeIndex] = DELETED; 
            printf("Key %d deleted from index %d.\n", key, probeIndex);
            return;
        }
    }

    printf("key %d does not exist in the table.\n", key);
}

void search() {
    int key, index, i;

    printf("\nEnter the key to search: ");
    scanf("%d", &key);

    index = (key % SIZE + SIZE) % SIZE; 

    for (i = 0; i < SIZE; i++) {
        int probeIndex = (index + i) % SIZE;
        if (array[probeIndex] == EMPTY) {
            printf("key %d does not exist in the table.\n", key);
            return;
        } else if (array[probeIndex] == key) {
            printf("key %d found at index %d.\n", key, probeIndex);
            return;
        }
    }

    printf("key %d does not exist in the table.\n", key);
}

void hash_table() {
    printf("\nHash Table:\n");
    for (int i = 0; i < SIZE; i++) {
        if (array[i] == EMPTY) {
            printf("%d -> Empty\n", i);
        } else if (array[i] == DELETED) {
            printf("%d -> Deleted\n", i);
        } else {
            printf("%d -> %d\n", i, array[i]);
        }
    }
}


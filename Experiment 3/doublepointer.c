#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void sortedInsert(struct Node** headRef, int data) {
    
    struct Node* newNode = createNode(data);
    struct Node* current;

    if (*headRef == NULL || (*headRef)->data >= newNode->data) {
        newNode->next = *headRef;
        *headRef = newNode;
    } else {
        current = *headRef;
        while (current->next != NULL && current->next->data < newNode->data) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void removeDuplicates(struct Node* head) {
    struct Node* current = head;
    struct Node* next_next;
    if (current == NULL)
        return;

    while (current->next != NULL) {
        if (current->data == current->next->data) {
            next_next = current->next->next;
            free(current->next);
            current->next = next_next;
        } else {
            current = current->next;
        }
    }
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int isValidInteger(const char* str) {
    char* endptr;
    strtol(str, &endptr, 10);
    if (*str == '\0' || *endptr != '\0') return 0;
    return 1;
}

void trimNewline(char* str) {
    char* pos;
    if ((pos = strchr(str, '\n')) != NULL) {
        *pos = '\0';
    }
}

int main() {
    struct Node* head = NULL;
    int n;
    char input[100];

    printf("num: ");
    fgets(input, sizeof(input), stdin);
    trimNewline(input);
    if (!isValidInteger(input)) {
        printf("input messed up please try again.\n");
        return 1;
    }
    n = atoi(input);

    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("element %d: ", i + 1);
        fgets(input, sizeof(input), stdin);
        trimNewline(input);
        if (!isValidInteger(input)) {
            printf("input messed up please try again.\n");
            i--; 
            continue;
        }
        int value = atoi(input);
        sortedInsert(&head, value);
    }
    printList(head);
    removeDuplicates(head);
    printList(head);

    return 0;
}

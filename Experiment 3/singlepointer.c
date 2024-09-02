#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* sortedInsert(struct Node* head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (!head || head->data >= data) {
        newNode->next = head;
        head = newNode;
    } 
    else {
        struct Node* current = head;
        while (current->next && current->next->data < data) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    return head;
}

struct Node* removeDuplicates(struct Node* head) {
    struct Node* current = head;

    while (current && current->next) {
        if (current->data == current->next->data) {
            struct Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
    return head;
}

void printList(struct Node* node) {
    while (node) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int n, data;

    printf("list length: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("element %d: ", i + 1);
        scanf("%d", &data);
        head = sortedInsert(head, data);
    }

    printf(":\n");
    printList(head);
    head = removeDuplicates(head);
    printf("\n");
    printList(head);
}

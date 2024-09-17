#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Node* head = NULL;

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

int getLength() {
    struct Node* temp = head;
    int length = 0;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}

void insertAtHead(int data) {
    struct Node* newNode = createNode(data);
    if (head == NULL) {
        head = newNode;
        return;
    }
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
}

void insertAtTail(int data) {
    struct Node* newNode = createNode(data);
    if (head == NULL) {
        head = newNode;
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void insertAtPosition(int data, int position) {
    if (position < 1 || position > getLength() + 1) {
        printf("Invalid position\n");
        return;
    }
    if (position == 1) {
        insertAtHead(data);
        return;
    }
    struct Node* newNode = createNode(data);
    struct Node* temp = head;
    for (int i = 1; i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        insertAtTail(data);
    } else {
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
    }
}

void deleteHead() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node* temp = head;
    head = head->next;
    if (head != NULL) head->prev = NULL;
    free(temp);
}

void deleteTail() {
    if (head == NULL) {
        printf("empty list\n");
        return;
    }
    struct Node* temp = head;
    if (head->next == NULL) {
        free(head);
        head = NULL;
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->prev->next = NULL;
    free(temp);
}

void deleteAtPosition(int position) {
    if (head == NULL || position < 1 || position > getLength()) {
        printf("wrong pos or emtpy list\n");
        return;
    }
    if (position == 1) {
        deleteHead();
        return;
    }
    struct Node* temp = head;
    for (int i = 1; i < position; i++) {
        temp = temp->next;
    }
    if (temp->prev != NULL) temp->prev->next = temp->next;
    if (temp->next != NULL) temp->next->prev = temp->prev;
    free(temp);
}

void displayForward() {
    struct Node* temp = head;
    if (head == NULL) {
        printf("empty list\n");
        return;
    }
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void displayBackward() {
    if (head == NULL) {
        printf("empty list\n");
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

int main() {

    deleteHead();      
    deleteTail();      
    deleteAtPosition(1); 

    insertAtHead(10);  
    displayForward();  

    insertAtHead(5);   
    displayForward();  

    insertAtTail(20);  
    displayForward();  

    insertAtPosition(15, 3);  
    displayForward();         

    insertAtPosition(25, 6);  

    insertAtPosition(25, 5);  
    displayForward();         

    deleteHead();   
    displayForward();  

    deleteTail();   
    displayForward();  

    deleteAtPosition(2);  
    displayForward();     

    deleteAtPosition(5);  

    displayForward();    
    displayBackward();   

    return 0;
}

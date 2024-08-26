#include <stdio.h>
#define MAX 100

typedef struct {
    int petrol;
    int distance;
} PetrolPump;

typedef struct {
    PetrolPump pumps[MAX];
    int front;
    int rear;
    int size;
} CircularQueue;

void enqueue(CircularQueue* q, PetrolPump item, int debug) {
    if (q->size == MAX) {
        if (debug) printf("DEBUG: Queue is full.\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX;
    q->pumps[q->rear] = item;
    q->size++;
    if (debug) printf("DEBUG: Enqueued: petrol = %d, distance = %d at position %d\n", item.petrol, item.distance, q->rear);
}

PetrolPump dequeue(CircularQueue* q, int debug) {
    PetrolPump item = {0, 0};
    if (q->size == 0) {
        if (debug) printf("DEBUG: Queue is empty.\n");
        return item;
    }
    item = q->pumps[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    if (debug) printf("DEBUG: Dequeued: petrol = %d, distance = %d from position %d\n", item.petrol, item.distance, q->front);
    return item;
}

int isTourPossible(CircularQueue* q, int n, int debug) {
    int fuel = 0;
    int count = 0;
    int start = q->front;

    if (debug) printf("DEBUG: Checking tour possibility starting at index %d\n", start);

    while (count < n) {
        PetrolPump current = dequeue(q, debug);
        fuel += current.petrol;

        if (debug) printf("DEBUG: Current fuel after adding pump = %d\n", fuel);

        if (fuel < current.distance) {
            if (debug) printf("DEBUG: Not enough fuel to cover distance from pump (petrol = %d, distance = %d). Tour is impossible.\n", current.petrol, current.distance);
            return 0;  
        }

        fuel -= current.distance;
        if (debug) printf("DEBUG: Fuel after covering distance = %d\n", fuel);

        enqueue(q, current, debug);  
        count++;
    }
    if (debug) printf("DEBUG: Tour is possible starting from index %d\n", start);
    return 1; 
}

int findFirstTour(PetrolPump pumps[], int n, int debug) {
    CircularQueue q = {.front = -1, .rear = -1, .size = 0};

    for (int i = 0; i < n; i++) {
        enqueue(&q, pumps[i], debug);
    }

    for (int i = 0; i < n; i++) {
        if (isTourPossible(&q, n, debug)) {
            return i; 
        }

        enqueue(&q, dequeue(&q, debug), debug);  
    }
    return -1; 
}

void displayTour(int start, int n) {
    printf("Tour: ");
    for (int i = 0; i < n; i++) {
        printf("%d->", (start + i) % n);
    }
    printf("%d\n", start);
}

void findAllPossibleTours(PetrolPump pumps[], int n, int debug) {
    CircularQueue q = {.front = -1, .rear = -1, .size = 0};

    for (int i = 0; i < n; i++) {
        enqueue(&q, pumps[i], debug);
    }

    for (int i = 0; i < n; i++) {
        if (isTourPossible(&q, n, debug)) {
            printf("Starting pump = %d\n", i);
            displayTour(i, n);
        }

        enqueue(&q, dequeue(&q, debug), debug);  
    }
}

int main() {
    PetrolPump pumps[] = {{4, 6}, {6, 5}, {7, 3}, {4, 5}};
    int n = sizeof(pumps) / sizeof(pumps[0]);
    int debug = 1;  

    int firstTour = findFirstTour(pumps, n, debug);
    if (firstTour != -1) {
        printf("Start for first proper tour = %d\n", firstTour);
        displayTour(firstTour, n);
    } else {
        printf("No possible tour found.\n");
    }

    printf("All possible tours:\n");
    findAllPossibleTours(pumps, n, debug);

    return 0;
}

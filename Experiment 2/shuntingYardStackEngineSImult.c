#include <stdbool.h>
#include <stdio.h>

#define MAX_HOLDING_TRACKS 100
#define MAX_CARS 100

typedef struct {
  int top;
  int cars[MAX_CARS];
} Stack;

void initializeStack(Stack *s) { s->top = -1; }

bool isEmpty(Stack *s) { return s->top == -1; }

bool isFull(Stack *s) { return s->top == MAX_CARS - 1; }

void push(Stack *s, int car) {
  if (!isFull(s)) {
    s->cars[++(s->top)] = car;
  }
}

int pop(Stack *s) {
  if (!isEmpty(s)) {
    return s->cars[(s->top)--];
  }
  return -1;
}

int peek(Stack *s) {
  if (!isEmpty(s)) {
    return s->cars[s->top];
  }
  return -1;
}

void moveCar(Stack *source, Stack *destination, bool debug) {
  int car = pop(source);
  push(destination, car);
  if (debug) {
    printf("Engine moved car %d from one holding track to another.\n", car);
  }
}

void printHoldingTracks(Stack *holdingTracks, int k) {
  for (int i = 0; i < k; i++) {
    printf("Holding Track H%d: ", i + 1);
    for (int j = 0; j <= holdingTracks[i].top; j++) {
      printf("%d ", holdingTracks[i].cars[j]);
    }
    printf("\n");
  }
}

void printOutputTrack(Stack *outputTrack, int size) {
  printf("Output Track: ");
  for (int i = 0; i <= outputTrack->top; i++) {
    printf("%d ", outputTrack->cars[i]);
  }
  printf("\n");
}

bool rearrangeCars(int n, int k, int *cars, bool debug) {
  if (n <= 0 || k < 3 || k > MAX_HOLDING_TRACKS) {
    printf("Invalid input.\n");
    return false;
  }

  Stack holdingTracks[3];
  initializeStack(&holdingTracks[0]);
  initializeStack(&holdingTracks[1]);
  initializeStack(&holdingTracks[2]);

  int nextExpectedCar = n;

  for (int i = 0; i < n; i++) {
    int car = cars[i];

    if (isEmpty(&holdingTracks[0]) || car < peek(&holdingTracks[0])) {
      push(&holdingTracks[0], car);
    } else {
      push(&holdingTracks[2], car);
    }
  }

  while (nextExpectedCar > 0) {
    bool carFound = false;

    while (!isEmpty(&holdingTracks[2]) && !carFound) {
      if (peek(&holdingTracks[2]) == nextExpectedCar) {
        push(&holdingTracks[1], pop(&holdingTracks[2]));
        carFound = true;
      } else {
        moveCar(&holdingTracks[2], &holdingTracks[0], debug);
      }
    }

    while (!isEmpty(&holdingTracks[0]) && !carFound) {
      if (peek(&holdingTracks[0]) == nextExpectedCar) {
        push(&holdingTracks[1], pop(&holdingTracks[0]));
        carFound = true;
      } else {
        moveCar(&holdingTracks[0], &holdingTracks[2], debug);
      }
    }

    if (carFound) {
      nextExpectedCar--;
    } else {
      printf("Failed to find the next expected car: %d\n", nextExpectedCar);
      return false;
    }

    if (debug) {
      printf("\nState of holding tracks:\n");
      printHoldingTracks(holdingTracks, 3);
    }
  }

  if (debug) {
    printf("\nFinal state of holding tracks:\n");
    printHoldingTracks(holdingTracks, 3);
  }

  printOutputTrack(&holdingTracks[1], holdingTracks[1].top + 1);
  return true;
}

int main() {
  int cars[] = {5, 8, 1, 7, 4, 2, 9, 6, 3};
  int n = sizeof(cars) / sizeof(cars[0]);
  int k = 3;
  bool debug = true;

  rearrangeCars(n, k, cars, debug);

  return 0;
}

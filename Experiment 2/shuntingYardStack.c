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
  for (int i = size - 1; i >= 0; i--) {
    printf("%d ", outputTrack->cars[i]);
  }
  printf("\n");
}

bool rearrangeCars(int n, int k, int *cars, bool debug) {
  if (n <= 0 || k <= 0 || k > MAX_HOLDING_TRACKS) {
    printf("Invalid input.\n");
    return false;
  }

  Stack holdingTracks[MAX_HOLDING_TRACKS];
  Stack outputTrack;
  initializeStack(&outputTrack);

  for (int i = 0; i < k; i++) {
    initializeStack(&holdingTracks[i]);
  }

  int nextExpectedCar = 1;

  if (debug) {
    printf("Initial cars: ");
    for (int i = 0; i < n; i++) {
      printf("%d ", cars[i]);
    }
    printf("\n\n");
  }

  for (int i = 0; i < n; i++) {
    int car = cars[i];

    if (car == nextExpectedCar) {
      push(&outputTrack, car);
      if (debug)
        printf("Move car %d directly to the output track.\n", car);
      nextExpectedCar++;
    } else {
      bool placed = false;
      for (int j = 0; j < k; j++) {
        if (isEmpty(&holdingTracks[j]) || peek(&holdingTracks[j]) > car) {
          push(&holdingTracks[j], car);
          if (debug)
            printf("Move car %d to holding track H%d.\n", car, j + 1);
          placed = true;
          break;
        }
      }
      if (!placed) {
        return false;
      }
    }

    for (int j = 0; j < k; j++) {
      while (!isEmpty(&holdingTracks[j]) &&
             peek(&holdingTracks[j]) == nextExpectedCar) {
        push(&outputTrack, pop(&holdingTracks[j]));
        if (debug)
          printf("Move car %d from holding track H%d to the output track.\n",
                 outputTrack.cars[outputTrack.top], j + 1);
        nextExpectedCar++;
      }
    }

    if (debug) {
      printf("\nState of holding tracks after processing car %d:\n", car);
      printHoldingTracks(holdingTracks, k);
      printf("State of output track:\n");
      printOutputTrack(&outputTrack, outputTrack.top + 1);
      printf("\n");
    }
  }

  if (debug) {
    printf("\nFinal state of holding tracks:\n");
    printHoldingTracks(holdingTracks, k);
    printf("Final state of output track:\n");
    printOutputTrack(&outputTrack, outputTrack.top + 1);
    printf("\n");
  }
  printOutputTrack(&outputTrack, outputTrack.top + 1);
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

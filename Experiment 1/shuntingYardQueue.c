#include <stdio.h>
#include <stdlib.h>

#define N 9
#define K 3

struct Queue {
  int data[N];
  int front, rear, size;
};

struct Queue *createQueue() {
  struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
  queue->front = 0;
  queue->rear = -1;
  queue->size = 0;
  return queue;
}

void enqueue(struct Queue *queue, int value) {
  if (queue->size == N) {
    printf("full\n");
    return;
  }
  queue->rear = (queue->rear + 1) % N;
  queue->data[queue->rear] = value;
  queue->size++;
}

int dequeue(struct Queue *queue) {
  if (queue->size == 0) {
    printf("empty\n");
    return -1;
  }
  int value = queue->data[queue->front];
  queue->front = (queue->front + 1) % N;
  queue->size--;
  return value;
}

int isEmpty(struct Queue *queue) { return queue->size == 0; }

void printQueue(struct Queue *queue) {
  int i = queue->front;
  for (int count = 0; count < queue->size; count++) {
    printf("%d ", queue->data[i]);
    i = (i + 1) % N;
  }
  printf("\n");
}

void printHoldingTracks(struct Queue *holdingTracks[], int k) {
  for (int j = 0; j < k; j++) {
    printf("H%d: ", j + 1);
    printQueue(holdingTracks[j]);
  }
}

int main() {

  int order[N] = {5, 8, 1, 7, 4, 2, 9, 6, 3};

  struct Queue *holdingTracks[K];
  for (int i = 0; i < K; i++) {
    holdingTracks[i] = createQueue();
  }
  int outIndex = 0;
  int output[N] = {0};

  for (int i = 0; i < N; i++) {
    int car = order[i];
    int placed = 0;

    for (int j = 0; j < K; j++) {
      if (isEmpty(holdingTracks[j]) ||
          car < holdingTracks[j]->data[holdingTracks[j]->rear]) {
        enqueue(holdingTracks[j], car);
        placed = 1;
        break;
      }
    }

    if (!placed) {
      printf("cant place %d anywhere so ig this array isnt possible\n", car);
      return -1;
    }

    printHoldingTracks(holdingTracks, K);
  }

  while (outIndex < N) {
    int maxCar = 0;
    int maxTrack = -1;

    for (int j = 0; j < K; j++) {
      if (!isEmpty(holdingTracks[j]) &&
          (maxTrack == -1 ||
           holdingTracks[j]->data[holdingTracks[j]->front] >
               holdingTracks[maxTrack]->data[holdingTracks[maxTrack]->front])) {
        maxTrack = j;
      }
    }

    if (maxTrack != -1) {
      output[outIndex++] = dequeue(holdingTracks[maxTrack]);
    }
  }

  for (int i = 0; i < N; i++) {
    printf("%d ", output[i]);
  }
  printf("\n");

  for (int i = 0; i < K; i++) {
    free(holdingTracks[i]);
  }

  return 0;
}

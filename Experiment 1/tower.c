#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000

typedef struct {
    int top;
    int items[MAX];
} Stack;
void push(Stack *st, int value) {
    st->items[++st->top] = value;
}
void pop(Stack *st) {
    if (st->top >= 0) {
        st->top--;
    }
}
int top(Stack *st) {
    return st->items[st->top];
}
int isEmpty(Stack *st) {
    return st->top == -1;
}

void calculateRange(int heights[], int n, int R[]) {
    Stack st;
    st.top = -1;
    push(&st, 0);
    R[0] = 1;

    for (int i = 1; i < n; i++) {
        while (!isEmpty(&st) && heights[top(&st)] <= heights[i]) {
            pop(&st);
        }

        R[i] = isEmpty(&st) ? (i + 1) : (i - top(&st));
        push(&st, i);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int t = 1;
    int n = 7;
    int heights[] = {100, 80, 60, 70, 60, 75, 85};
    int *R = (int*)malloc(n * sizeof(int));

    calculateRange(heights, n, R);
    printArray(R, n);

    free(R);

    return 0;
}

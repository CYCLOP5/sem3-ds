#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    int items[MAX];
    int top;
} Stack;

void push(Stack *stack, int val) {
    if (stack->top < MAX - 1) {
        stack->items[++stack->top] = val;
    }
}

int pop(Stack *stack) {
    if (stack->top != -1) {
        return stack->items[stack->top--];
    }
    return -1;
}

void displayStack(Stack *stack) {
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->items[i]);
    }
    printf("\n");
}

int evaluatePostfix(char* expr) {
    Stack stack;
    stack.top = -1;

    int i = 0;
    
    while (expr[i] != '\0') {
        if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            push(&stack, num);
            displayStack(&stack);
        } else if (expr[i] == ' ') {
            i++;
        } else {
            int val2 = pop(&stack);
            int val1 = pop(&stack);
            switch (expr[i]) {
                case '+': push(&stack, val1 + val2); break;
                case '-': push(&stack, val1 - val2); break;
                case '*': push(&stack, val1 * val2); break;
                case '/': push(&stack, val1 / val2); break;
            }
            displayStack(&stack);
            i++;
        }
    }
    return pop(&stack);
}

int main() {
    char expr[MAX];
    printf("lmao: ");
    fgets(expr, MAX, stdin);
    expr[strcspn(expr, "\n")] = 0;
    printf("%d\n", evaluatePostfix(expr));
    return 0;
}

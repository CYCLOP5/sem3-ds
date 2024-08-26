#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int val) {
    if (top < MAX - 1) {
        stack[++top] = val;
    }
}

int pop() {
    if (top != -1) {
        return stack[top--];
    }
    return -1;
}

void displayStack() {
    for (int i = 0; i <= top; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int test(char* expr) {
    int i = 0;
    while (expr[i] != '\0') {
        if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            push(num);
            displayStack();
        } else if (expr[i] == ' ') {
            i++;
        } else {
            int val2 = pop();
            int val1 = pop();
            switch (expr[i]) {
                case '+': push(val1 + val2); break;
                case '-': push(val1 - val2); break;
                case '*': push(val1 * val2); break;
                case '/': push(val1 / val2); break;
            }
            displayStack();
            i++;
        }
    }
    return pop();
}

int main() {
    char expr[MAX];
    printf("lmao: ");
    fgets(expr, MAX, stdin);
    expr[strcspn(expr, "\n")] = 0;
    printf("%d",test(expr));
    return 0;
}

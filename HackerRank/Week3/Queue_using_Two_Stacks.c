#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000

typedef struct {
    int arr[SIZE];
    int top;
} Stack;

void stack_push(Stack *s, int val) {
    s->arr[++s->top] = val;
}

int stack_pop(Stack *s) {
    return s->arr[s->top--];
}

int stack_top(Stack *s) {
    return s->arr[s->top];
}

int stack_empty(Stack *s) {
    return s->top < 0;
}

int main() {
    int queries;
    scanf("%d", &queries);

    Stack first, second;
    first.top = -1;
    second.top = -1;

    while (queries--) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            int value;
            scanf("%d", &value);
            stack_push(&first, value);
        } else {
            if (stack_empty(&second)) {
                while (!stack_empty(&first)) {
                    stack_push(&second, stack_pop(&first));
                }
            }
            if (type == 2) {
                stack_pop(&second);
            } else if (type == 3) {
                printf("%d\n", stack_top(&second));
            }
        }
    }

    return 0;
}

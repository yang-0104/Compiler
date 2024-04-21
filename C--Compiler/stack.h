#ifndef STACK_H
#define STACK_H

typedef struct
{
    int *items;
    int top;
} Stack;

void initialize(Stack *stack);
int isEmpty(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
int peek_stack(Stack *stack);

#endif /* STACK_OPERATIONS_H */
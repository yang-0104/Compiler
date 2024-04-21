#include<iostream>
#include "stack.h" 

// 初始化栈
void initialize(Stack *stack)
{
    stack->top = -1;
    stack->items = NULL;
}

// 判断栈是否为空
int isEmpty(Stack *stack)
{
    return stack->top == -1;
}

// 入栈操作
void push(Stack *stack, int value)
{
    stack->top++;

    // 动态分配内存，每次扩展栈大小
    stack->items = (int *)realloc(stack->items, (stack->top + 1) * sizeof(int *));

    if (stack->items == NULL)
    {
        printf("内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    stack->items[stack->top] = value;
    // printf("%c 入栈成功\n", value);
}

// 出栈操作
int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("栈为空，无法出栈\n");
        return -1; // 表示出栈失败
    }
    else
    {
        int poppedItem = stack->items[stack->top];
        stack->top--;

        // 动态缩小内存，每次缩小一个元素
        stack->items = (int *)realloc(stack->items, (stack->top + 1) * sizeof(int *));

        // printf("%d 出栈成功\n", poppedItem);
        return poppedItem;
    }
}

// 获取栈顶元素
int peek_stack(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("栈为空\n");
        return -1; // 表示栈为空
    }
    else
    {
        return stack->items[stack->top];
    }
}
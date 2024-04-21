#include<iostream>
#include "stack.h" 

// ��ʼ��ջ
void initialize(Stack *stack)
{
    stack->top = -1;
    stack->items = NULL;
}

// �ж�ջ�Ƿ�Ϊ��
int isEmpty(Stack *stack)
{
    return stack->top == -1;
}

// ��ջ����
void push(Stack *stack, int value)
{
    stack->top++;

    // ��̬�����ڴ棬ÿ����չջ��С
    stack->items = (int *)realloc(stack->items, (stack->top + 1) * sizeof(int *));

    if (stack->items == NULL)
    {
        printf("�ڴ����ʧ��\n");
        exit(EXIT_FAILURE);
    }
    stack->items[stack->top] = value;
    // printf("%c ��ջ�ɹ�\n", value);
}

// ��ջ����
int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("ջΪ�գ��޷���ջ\n");
        return -1; // ��ʾ��ջʧ��
    }
    else
    {
        int poppedItem = stack->items[stack->top];
        stack->top--;

        // ��̬��С�ڴ棬ÿ����Сһ��Ԫ��
        stack->items = (int *)realloc(stack->items, (stack->top + 1) * sizeof(int *));

        // printf("%d ��ջ�ɹ�\n", poppedItem);
        return poppedItem;
    }
}

// ��ȡջ��Ԫ��
int peek_stack(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("ջΪ��\n");
        return -1; // ��ʾջΪ��
    }
    else
    {
        return stack->items[stack->top];
    }
}
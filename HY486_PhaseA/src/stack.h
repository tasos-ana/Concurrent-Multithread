#ifndef STACK_H
#define STACK_H

#include <stdio.h>

stack_p concurrentStack;

typedef struct stackNode {
    int action;
    int fileID;
    int newFileSize;
    struct stackNode* next;
} *stackNode_p, stackNode_t;

typedef struct stack {
    stackNode_p top;
    pthread_mutex_t mutex;
} *stack_p, stack_t;

void initStack(void);

int isEmptyStack();

stackNode_p createNode(int action, int fileID, int newFileSize);

int push(stackNode_p node);

stackNode_p pop();

void printStack();
#endif // STACK_H


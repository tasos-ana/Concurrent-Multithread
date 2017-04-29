#ifndef STACK_H
#define STACK_H

#include <stdio.h>

typedef struct stackNode {
    int action;
    int fileID;
    int newFileSize;
    struct stackNode* next;
} *stackNode_p, stackNode_s;

typedef struct stack {
    stackNode_p top;
    pthread_mutex_t mutex;
} *stack_p, stack_s;

stack_p modStack;

pthread_mutex_t printMutex;

void initStack(void);

int isEmptyStack(void);

stackNode_p createNode(int action, int fileID, int newFileSize);

void push(stackNode_p node);

stackNode_p pop(void);

void lock(pthread_mutex_t *mutex);

void unlock(pthread_mutex_t *mutex);

void printStack(void);

void printStackItem(stackNode_p item, int threadID);

void cleanStack(void);
#endif // STACK_H


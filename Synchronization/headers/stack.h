/* * * * * * * * * * * * * * * *\
 *                             *
 * General Functions of Stack  *
 *                             *
 * File:    headers/stack.h    *
 * Author:  Tasos Anastasas    *
 * A.M:     3166               *
 * Course:  CS486              *
 * Project: 2017               *
 * Phase:   1                  *
\* * * * * * * * * * * * * * * */

#ifndef STACK_H
#define STACK_H

#include <sys/types.h>

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

pthread_mutex_t printStackMutex;

void initStack(void);

int isEmptyStack(void);

stackNode_p createStackNode(int action, int fileID, int newFileSize);

void pushStack(stackNode_p node);

stackNode_p popStack(void);

void printStack(void);

void printStackItem(stackNode_p item, int threadID);

void cleanStack(void);
#endif // STACK_H


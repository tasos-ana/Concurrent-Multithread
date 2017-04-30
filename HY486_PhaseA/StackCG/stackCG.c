/*
 * implementation: Coarse Grained Stack withou elimination array
 */
#include <stdio.h>
#include <stdlib.h>

#include "../headers/stack.h"
#include "../headers/utils.h"

void initStack(void) {
    modStack = (stack_p) malloc(sizeof (stack_s));
    modStack->top = NULL;
    initMutex(&(modStack->mutex));
    initMutex(&printStackMutex);
}

void pushStack(stackNode_p node) {
    lock(&(modStack->mutex));
    node->next = modStack->top;
    modStack->top = node;
    unlock(&(modStack->mutex));
}

stackNode_p popStack(void) {
    lock(&(modStack->mutex));
    stackNode_p tmp = modStack->top;
    if (tmp != NULL) {
        modStack->top = tmp->next;
    }
    unlock(&(modStack->mutex));

    return tmp;
}

void cleanStack(void) {
    //free the stack
    stackNode_p current = modStack->top, tmp;
    while (current != NULL) {
        tmp = current;
        current = current->next;
        free(tmp);
        tmp = NULL;
    }

    destroyMutex(&(modStack->mutex));
    destroyMutex(&printStackMutex);

    free(modStack);
    modStack = NULL;
}
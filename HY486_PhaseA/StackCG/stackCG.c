/*
 * implementation: Coarse Grained Stack withou elimination array
 */
#include <stdio.h>
#include <stdlib.h>

#include "../headers/stack.h"
#include "../headers/utils.h"

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
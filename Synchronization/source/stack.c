/* * * * * * * * * * * * * * * *\
 *                             *
 * General Functions of Stack  *
 *                             *
 * File:    source/stack.c     *
 * Author:  Tasos Anastasas    *
 * A.M:     3166               *
 * Course:  CS486              *
 * Project: 2017               *
 * Phase:   1                  *
\* * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#include "../headers/stack.h"
#include "../headers/utils.h"

int isEmptyStack() {
    lock(&(modStack->mutex));
    int retVal = (modStack->top == NULL);
    unlock(&(modStack->mutex));

    return retVal;
}

stackNode_p createStackNode(int action, int fileID, int newFileSize) {
    stackNode_p node = (stackNode_p) malloc(sizeof (stackNode_s));
    node->action = action;
    node->fileID = fileID;
    node->newFileSize = newFileSize;
    node->next = NULL;

    return node;
}

void printStack() {
    printf("Print stack:\n");
    if (isEmptyStack()) {
        printf("Empty\n");
        return;
    } else {
        lock(&(modStack->mutex));

        stackNode_p current = modStack->top;
        while (current != NULL) {
            printf("%c ", (char) (current->action));
            if (current->fileID != -1) {
                printf("%d ", current->fileID);
            }
            if (current->newFileSize != -1) {
                printf("%d ", current->newFileSize);
            }
            printf("\n");
            current = current->next;
        }

        unlock(&(modStack->mutex));
    }
}

void printStackItem(stackNode_p item, int threadID) {
    lock(&printStackMutex);
    if (item != NULL) {
        printf("%c ", (char) (item->action));
        printf("%d ", threadID);
        if (item->fileID != -1) {
            printf("%d ", item->fileID);
        }
        if (item->newFileSize != -1) {
            printf("%d ", item->newFileSize);
        }
        printf("\n");
        fflush(stdout);
    }
    unlock(&printStackMutex);
}
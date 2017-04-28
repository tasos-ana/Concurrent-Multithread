#include <stdio.h>
#include <stdlib.h>

#include "../src/stack.h"
#include "../src/utils.h"

void initStack(void) {
    int status;
    modStack = (stack_p) malloc(sizeof (stack_s));
    modStack->top = NULL;
    status = pthread_mutex_init(&(modStack->mutex), NULL);
    if (status != 0) {
        handle_error_en(status, "pthread_mutex_init");
    }
}

int isEmptyStack() {
    return (modStack->top == NULL);
}

stackNode_p createNode(int action, int fileID, int newFileSize) {
    stackNode_p node = (stackNode_p) malloc(sizeof (stackNode_s));
    node->action = action;
    node->fileID = fileID;
    node->newFileSize = newFileSize;
    node->next = NULL;

    return node;
}

void push(stackNode_p node) {
    int status;
    if ((status = pthread_mutex_lock(&(modStack->mutex))) != 0) {
        handle_error_en(status, "pthread_mutex_lock");
    }

    node->next = modStack->top;
    modStack->top = node;

    if ((status = pthread_mutex_unlock(&(modStack->mutex))) != 0) {
        handle_error_en(status, "pthread_mutex_unlock");
    }
}

stackNode_p pop() {
    if (isEmptyStack()) {
        return NULL;
    } else {
        int status;
        if ((status = pthread_mutex_lock(&(modStack->mutex))) != 0) {
            handle_error_en(status, "pthread_mutex_lock");
        }

        stackNode_p tmp = modStack->top;
        modStack->top = tmp->next;

        if ((status = pthread_mutex_unlock(&(modStack->mutex))) != 0) {
            handle_error_en(status, "pthread_mutex_unlock");
        }

        return tmp;
    }
}

void printStack() {
    if (isEmptyStack()) {
        return;
    } else {
        int status;
        if ((status = pthread_mutex_lock(&(modStack->mutex))) != 0) {
            handle_error_en(status, "pthread_mutex_lock");
        }

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

        if ((status = pthread_mutex_unlock(&(modStack->mutex))) != 0) {
            handle_error_en(status, "pthread_mutex_unlock");
        }
    }
}
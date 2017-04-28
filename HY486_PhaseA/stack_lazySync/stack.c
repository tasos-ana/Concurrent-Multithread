#include <stdio.h>
#include <stdlib.h>

#include "../src/stack.h"
#include "../src/utils.h"

void initStack(void) {
    int status;
    concurrentStack = (stack_p) malloc(sizeof (stack_t));
    concurrentStack->top = NULL;
    status = pthread_mutex_init(&concurrentStack->mutex, NULL);
    if (status != 0) {
        handle_error_en(status, "pthread_mutex_init");
    }
}

int isEmptyStack() {
    return (concurrentStack->top == NULL);
}

stackNode_p createNode(int action, int fileID, int newFileSize) {
    stackNode_p node = (stackNode_p) malloc(sizeof (stackNode_t));
    node->action = action;
    node->fileID = fileID;
    node->newFileSize = newFileSize;
    node->next = NULL;

    return node;
}

int push(stackNode_p node) {
    int status;
    if ((status = pthread_mutex_lock(&(concurrentStack->mutex))) != 0) {
        handle_error_en(status, "pthread_mutex_lock");
    }

    node->next = concurrentStack->top;
    concurrentStack->top = node;

    if ((status = pthread_mutex_unlock(&(concurrentStack->mutex))) != 0) {
        handle_error_en(status, "pthread_mutex_unlock");
    }
}

stackNode_p pop() {
    if (isEmptyStack()) {
        return NULL;
    } else {
        int status;
        if ((status = pthread_mutex_lock(&(concurrentStack->mutex))) != 0) {
            handle_error_en(status, "pthread_mutex_lock");
        }

        stackNode_p tmp = concurrentStack->top;
        concurrentStack->top = tmp->next;

        if ((status = pthread_mutex_unlock(&(concurrentStack->mutex))) != 0) {
            handle_error_en(status, "pthread_mutex_unlock");
        }
    }
}

void printStack() {
    if (isEmptyStack()) {
        return NULL;
    } else {
        int status;
        if ((status = pthread_mutex_lock(&(concurrentStack->mutex))) != 0) {
            handle_error_en(status, "pthread_mutex_lock");
        }

        stackNode_p current = concurrentStack->top;
        while (current != NULL) {
            printf("%c %d %d \n", (char) (current->action), current->fileID, current->newFileSize);
            current = current->next;
        }

        if ((status = pthread_mutex_unlock(&(concurrentStack->mutex))) != 0) {
            handle_error_en(status, "pthread_mutex_unlock");
        }
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

    status = pthread_mutex_init(&printMutex, NULL);
    if (status != 0) {
        handle_error_en(status, "pthread_mutex_init");
    }
}

int isEmptyStack() {
    lock(&(modStack->mutex));

    int retVal = (modStack->top == NULL);

    unlock(&(modStack->mutex));

    return retVal;
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
    lock(&(modStack->mutex));

    node->next = modStack->top;
    modStack->top = node;

    unlock(&(modStack->mutex));
}

stackNode_p pop(void) {
    lock(&(modStack->mutex));
    stackNode_p tmp = modStack->top;
    if (tmp != NULL) {
        modStack->top = tmp->next;
    }
    unlock(&(modStack->mutex));

    return tmp;
}

void lock(pthread_mutex_t *mutex) {
    int status;
    if ((status = pthread_mutex_lock(mutex)) != 0) {
        handle_error_en(status, "pthread_mutex_lock");
    }
}

void unlock(pthread_mutex_t *mutex) {
    int status;
    if ((status = pthread_mutex_unlock(mutex)) != 0) {
        handle_error_en(status, "pthread_mutex_unlock");
    }
}

void printStack() {
    if (isEmptyStack()) {
        printf("Empty stack\n");
        return;
    } else {
        lock(&(modStack->mutex));

        printf("Print stack:\n");
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
    lock(&printMutex);
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
    unlock(&printMutex);
}

void cleanStack(void) {
    
    lock(&(modStack->mutex));

    //free the stack
    stackNode_p current = modStack->top, tmp;
    while (current != NULL) {
        tmp = current;
        current = current->next;
        free(tmp);
        tmp = NULL;
    }

    unlock(&(modStack->mutex));

    int status = pthread_mutex_destroy(&(modStack->mutex));
    if (status != 0) {
        handle_error_en(status, "pthread_mutex_destroy");
    }

    free(modStack);
    modStack = NULL;

    status = pthread_mutex_destroy(&printMutex);
    if (status != 0) {
        handle_error_en(status, "pthread_mutex_destroy");
    }
}
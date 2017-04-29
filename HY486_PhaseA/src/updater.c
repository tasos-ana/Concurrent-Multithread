#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#include "updater.h"
#include "utils.h"
#include "stack.h"

void* updaterLogic(void * id) {
    int threadID = *((int*) id);
    int status;

    if ((status = pthread_mutex_unlock(&initThreadsLock)) != 0) {
        handle_error_en(status, "pthread_mutex_unlock");
    }

    while (1) {
        if (clientsDone && isEmptyStack()) {
            assert(modStack->top == NULL);
            break;
        } else {
            stackNode_p item = pop();
            printStackItem(item, threadID);
            free(item);
            item = NULL;
        }
    }

    return NULL;
}

void updaterInsert(int threadID, int id, int fileID, int fileSize) {

}

void updaterLookup(int threadID, int id, int fileID) {

}

void updaterModify(int threadID, int id, int fileID, int newFileSize) {

}

void updaterDelete(int threadID, int id, int fileID) {

}

void updaterPrint(int threadID, int id) {

}

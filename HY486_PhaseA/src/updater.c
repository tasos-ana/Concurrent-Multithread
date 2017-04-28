#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "updater.h"
#include "utils.h"
#include "stack.h"

void* updaterLogic(void * threadID) {
    int id = *((int*) threadID);
    int status;

    if ((status = pthread_mutex_unlock(&initThreadsLock)) != 0) {
        handle_error_en(status, "pthread_mutex_unlock");
    }

    while (1) {
        if (isEmptyStack() && clientsDone) {
            break;
        } else {
            stackNode_p item = pop();
            if (item != NULL) {
                printf("%c ", (char) (item->action));
                printf("%d ", id);
                if (item->fileID != -1) {
                    printf("%d ", item->fileID);
                }
                if (item->newFileSize != -1) {
                    printf("%d ", item->newFileSize);
                }
                printf("\n");
            }
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

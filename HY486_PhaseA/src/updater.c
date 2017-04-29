#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "updater.h"
#include "utils.h"
#include "stack.h"
#include "list.h"

void initUpdaters(void) {
    total_operations = 0;
    clientsDone = 0;
    initMutex(&totalOperationMutex);
}

void* updaterLogic(void * id) {
    int threadID = *((int*) id);

    unlock(&initThreadsLock);

    while (1) {
        if (clientsDone && isEmptyStack()) {
            assert(modStack->top == NULL);
            break;
        } else {
            stackNode_p item = popStack();
            if (item != NULL) {
                char ev = (char) (item->action);
                switch (ev) {
                    case 'I':
                        assert(item->fileID != -1);
                        assert(item->newFileSize != -1);
                        updaterInsert(threadID, item->fileID, item->newFileSize);
                        break;
                    case 'L':
                        assert(item->fileID != -1);
                        assert(item->newFileSize == -1);
                        updaterLookup(threadID, item->fileID);
                        break;
                    case 'M':
                        //assert(item->fileID != -1);
                        //assert(item->newFileSize != -1);
                        //updaterModify(threadID, item->fileID, item->newFileSize);
                        break;
                    case 'D':
                        assert(item->fileID != -1);
                        assert(item->newFileSize == -1);
                        updaterDelete(threadID, item->fileID);
                        break;
                    default:
                        handle_error("Invalid event");
                }
                free(item);
                item = NULL;
            }
        }
    }

    return NULL;
}

void updaterInsert(int threadID, int fileID, int fileSize) {
    int retVal;
    retVal = insertList(fileID, fileSize);
    printf("I %d %d %d %s\n", threadID, fileID, fileSize, retVal ? "SUCCEEDED" : "FAILED");
    increaseOperations();
}

void updaterLookup(int threadID, int fileID) {
    int retVal;
    retVal = lookupList(fileID);


    if (retVal != -1) {
        printf("L %d %d %d SUCCEEDED\n", threadID, fileID, retVal);
    } else {
        printf("L %d %d FAILED\n", threadID, fileID);
    }
    increaseOperations();
}

void updaterModify(int threadID, int fileID, int newFileSize) {
    int retVal = 0;
    int oldFileSize = 0;

    if (retVal) {
        printf("M %d %d %d %d SUCCEEDED\n", threadID, fileID, oldFileSize, newFileSize);
    } else {
        printf("M %d %d FAILED\n", threadID, fileID);
    }

    increaseOperations();
}

void updaterDelete(int threadID, int fileID) {
    int retVal;
    retVal = deleteList(fileID);
    if (retVal != -1) {
        printf("D %d %d %d SUCCEEDED\n", threadID, fileID, retVal);
    } else {
        printf("D %d %d FAILED\n", threadID, fileID);
    }
    fflush(stdout);
    increaseOperations();
}

void increaseOperations(void) {
    lock(&totalOperationMutex);
    total_operations += 1;
    unlock(&totalOperationMutex);
}

void cleanUpdaters(void) {
    destroyMutex(&totalOperationMutex);
}
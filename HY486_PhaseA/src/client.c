#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>

#include "client.h"
#include "stack.h"
#include "utils.h"

void* clientLogic(void * threadID) {
    int id = *((int*) threadID);
    int unlock;
    FILE *fp;
    char buf[1024];
    char ev;

    if ((unlock = pthread_mutex_unlock(&initThreadsLock)) != 0) {
        handle_error_en(unlock, "pthread_mutex_unlock");
    }
    assert(filepath != NULL);
    fp = fopen(filepath, "r");
    if (fp == NULL) {
        handle_error("fopen");
    }

    while (fgets(buf, sizeof (buf), fp) != NULL) {
        buf[strcspn(buf, "\n")] = '\0';
        tokenize(buf);
        ev = *tokens[0];
        int fileID;
        switch (ev) {
            case 'I':
                clientInsert(id, asint[1], asint[2], asint[3]);
                break;
            case 'L':
                fileID = asint[1];
                if (id == fileID) {
                    printf("L=%d %d %d\n", (int) 'L', asint[1], asint[2]);
                }
                break;
            case 'M':
                fileID = asint[1];
                if (id == fileID) {
                    printf("M=%d %d %d\n", asint[0], asint[1], asint[2]);
                }
                break;
            case 'D':
                fileID = asint[1];
                if (id == fileID) {
                    printf("D=%d %d %d\n", asint[0], asint[1], asint[2]);
                }
                break;
            case 'B':
                printf("B=%d\n", asint[0]);
                break;
            case 'P':
                fileID = asint[1];
                if (id == fileID) {
                    printf("M=%d %d\n", asint[0], asint[1]);
                }
                break;
            default:
                fprintf(stderr, "Invalid event");
                return;
        }
    }

    fclose(fp);
}

/*
 *  insert  :   73
 *  lookup  :   76
 *  modify  :   77
 *  delete  :   68
 */
void clientInsert(int threadID, int id, int fileID, int fileSize) {
    if (threadID == id) {
        int ret;
        ret = push(createNode((int) 'I', fileID, fileSize));
        printf("I %d %d %d %s\n", threadID, fileID, fileSize, ret ? "SUCCEEDED" : "FAILED");
    }
}

void clientLookup(int threadID, int id, int fileID) {
    if (threadID == id) {

    }
}

void clientModify(int threadID, int id, int fileID, int newFileSize) {
    if (threadID == id) {

    }
}

void clientDelete(int threadID, int id, int fileID) {
    if (threadID == id) {

    }
}

void clientBarrier(int threadID, int wait) {
    if (wait == 1) {
        printf("%d BARRIER WAIT\n", threadID);
    } else {
        printf("%d BARRIER CONTINUE\n", threadID);
    }
}
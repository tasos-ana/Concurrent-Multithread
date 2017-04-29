#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>

#include "client.h"
#include "stack.h"
#include "utils.h"

void* clientLogic(void * id) {
    int threadID = *((int*) id);
    int status;
    FILE *fp;
    char buf[1024];
    char ev;

    char *tokens[LEN_TOKENS];
    int asint[LEN_TOKENS];

    if ((status = pthread_mutex_unlock(&initThreadsLock)) != 0) {
        handle_error_en(status, "pthread_mutex_unlock");
    }
    assert(filepath != NULL);
    fp = fopen(filepath, "r");
    if (fp == NULL) {
        handle_error("fopen");
    }

    while (fgets(buf, sizeof (buf), fp) != NULL) {
        buf[strcspn(buf, "\n")] = '\0';
        tokenize(tokens, asint, buf);
        ev = *tokens[0];
        switch (ev) {
            case 'I':
                clientInsert(threadID, asint[1], asint[2], asint[3]);
                break;
            case 'L':
                clientLookup(threadID, asint[1], asint[2]);
                break;
            case 'M':
                clientModify(threadID, asint[1], asint[2], asint[3]);
                break;
            case 'D':
                clientDelete(threadID, asint[1], asint[2]);
                break;
            case 'B':
                barrier(threadID, 1);
                pthread_barrier_wait(&clientBarrier);
                barrier(threadID, 0);
                break;
            case 'P':
                clientPrint(threadID, asint[1]);
                break;
            default:
                fclose(fp);
                handle_error("Invalid event");
        }
    }
    fclose(fp);

    return NULL;
}

/*
 *  insert  :   73
 *  lookup  :   76
 *  modify  :   77
 *  delete  :   68
 */
void clientInsert(int threadID, int id, int fileID, int fileSize) {
    if (threadID == id) {
        push(createNode((int) 'I', fileID, fileSize));
    }
}

void clientLookup(int threadID, int id, int fileID) {
    if (threadID == id) {
        push(createNode((int) 'L', fileID, -1));
    }
}

void clientModify(int threadID, int id, int fileID, int newFileSize) {
    if (threadID == id) {
        push(createNode((int) 'M', fileID, newFileSize));
    }
}

void clientDelete(int threadID, int id, int fileID) {
    if (threadID == id) {
        push(createNode((int) 'D', fileID, -1));
    }
}

void barrier(int threadID, int wait) {
    if (wait == 1) {
        printf("%d BARRIER WAIT\n", threadID);
    } else {
        printf("%d BARRIER CONTINUE\n", threadID);
    }
}

void clientPrint(int threadID, int id) {
    if (threadID == id) {
        push(createNode((int) 'P', -1, -1));
    }
}

void cleanClient(void) {
    int status = pthread_barrier_destroy(&clientBarrier);
    if (status != 0) {
        handle_error_en(status, "pthread_barrier_destroy");
    }

    free(filepath);
    filepath = NULL;
}
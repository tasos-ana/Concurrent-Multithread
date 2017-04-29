#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>

#include "client.h"
#include "stack.h"
#include "utils.h"

void initClients(char* file, int clients) {
    filepath = file;
    initBarrier(&clientBarrier, clients);
}

void* clientLogic(void * id) {
    int threadID = *((int*) id);
    FILE *fp;
    char buf[1024];
    char ev;

    char *tokens[LEN_TOKENS];
    int asint[LEN_TOKENS];

    unlock(&initThreadsLock);

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
                //barrier(threadID, 1);
                pthread_barrier_wait(&clientBarrier);
                //barrier(threadID, 0);
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
        pushStack(createStackNode((int) 'I', fileID, fileSize));
    }
}

void clientLookup(int threadID, int id, int fileID) {
    if (threadID == id) {
        pushStack(createStackNode((int) 'L', fileID, -1));
    }
}

void clientModify(int threadID, int id, int fileID, int newFileSize) {
    if (threadID == id) {
        pushStack(createStackNode((int) 'M', fileID, newFileSize));
    }
}

void clientDelete(int threadID, int id, int fileID) {
    if (threadID == id) {
        pushStack(createStackNode((int) 'D', fileID, -1));
    }
}

void barrier(int threadID, int wait) {
    if (wait == 1) {
        printf("%d BARRIER WAIT\n", threadID);
    } else {
        printf("%d BARRIER CONTINUE\n", threadID);
    }
}

void cleanClient(void) {
    destroyBarrier(&clientBarrier);
    free(filepath);
    filepath = NULL;
}
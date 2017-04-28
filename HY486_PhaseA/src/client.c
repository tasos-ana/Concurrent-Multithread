#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "client.h"
#include "utils.h"
#include "updater.h"

void* clientLogic(void * threadID) {
    int id = *((int*) threadID);
    int unlock;
    printf("clientCREATED with ID: %d and path: %s\n", id, filepath);
    unlock = pthread_mutex_unlock(&initThreadsLock);
    if (unlock != 0) {
        handle_error_en(unlock, "pthread_mutex_unlock");
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "updater.h"
#include "utils.h"

void* updaterLogic(void * threadID) {
    // int id = *((int*) threadID);
    int unlock;

    if ((unlock = pthread_mutex_unlock(&initThreadsLock)) != 0) {
        handle_error_en(unlock, "pthread_mutex_unlock");
    }
    return NULL;
}

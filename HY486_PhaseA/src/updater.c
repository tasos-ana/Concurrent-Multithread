#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "updater.h"
#include "utils.h"

void* updaterLogic(void * threadID) {
    int id = *((int*) threadID);
    int unlock;
    printf("updaterCREATED with ID: %d\n", id);
    if ((unlock = pthread_mutex_unlock(&initThreadsLock)) != 0) {
        handle_error_en(unlock, "pthread_mutex_unlock");
    }
}

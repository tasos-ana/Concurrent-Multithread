/* * * * * * * * * * * * * * * * * * * * *\
 *                                       *
 * Functions required on different files *
 *                                       *
 * File:    source/utils.c               *
 * Author:  Tasos Anastasas              *
 * A.M:     3166                         *
 * Course:  CS486                        *
 * Project: 2017                         *
 * Phase:   1                            *
\* * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

#include "../headers/utils.h"

void usage(void) {
    printf("Usage: prog -c clientNum -u updaterNum -f file"
            "Options:\n"
            "   -c <int>            Set the clients thread number.\n"
            "   -u <int>            Set the updater thread number.\n"
            "   -f <string>         Set -f option specifies the file path of the input.\n"
            "   -h                  prints this help\n");
}

void tokenize(char **tokens, int *asint, char *s) { /*tokenization of input arguments*/
    char *p, *last;
    int i = 0;
    for ((p = strtok_r(s, " ", &last)); p;
            (p = strtok_r(NULL, " ", &last))) {
        if (i < LEN_TOKENS - 1) {
            tokens[i] = p;
            asint[i] = atoi(p);
            i++;
        }
    }
    tokens[i] = NULL;
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

void initMutex(pthread_mutex_t *mutex) {
    int status = pthread_mutex_init(mutex, NULL);
    if (status != 0) {
        handle_error_en(status, "pthread_mutex_init");
    }
}

void destroyMutex(pthread_mutex_t *mutex) {
    int status = pthread_mutex_destroy(mutex);
    if (status != 0) {
        handle_error_en(status, "pthread_mutex_destroy");
    }
}

void initBarrier(pthread_barrier_t *barrier, int num) {
    int status = pthread_barrier_init(barrier, NULL, num);
    if (status != 0) {
        handle_error_en(status, "pthread_barrier_init");
    }
}

void destroyBarrier(pthread_barrier_t *barrier) {
    int status = pthread_barrier_destroy(barrier);
    if (status != 0) {
        handle_error_en(status, "pthread_barrier_destroy");
    }
}

long getNanos(void) {
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        return (long) now.tv_sec * 1000000000 + now.tv_nsec;
    }
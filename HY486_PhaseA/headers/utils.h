/* * * * * * * * * * * * * * * * * * * * *\
 *                                       *
 * Functions required on different files *
 *                                       *
 * File:    headers/utils.h              *
 * Author:  Tasos Anastasas              *
 * A.M:     3166                         *
 * Course:  CS486                        *
 * Project: 2017                         *
 * Phase:   1                            *
\* * * * * * * * * * * * * * * * * * * * */
#ifndef UTIL_H
#define UTIL_H


#include <errno.h>
#include <sys/types.h>

#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
               do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define LEN_TOKENS 128

pthread_mutex_t initThreadsLock;

int maxThreadNum;

void usage(void);

void tokenize(char **tokens, int *asint, char *s); /*tokenization of input arguments*/

void lock(pthread_mutex_t *mutex);

void unlock(pthread_mutex_t *mutex);

void initMutex(pthread_mutex_t *mutex);

void destroyMutex(pthread_mutex_t *mutex);

void initBarrier(pthread_barrier_t *barrier, int num);

void destroyBarrier(pthread_barrier_t *barrier);

int isExpired(struct timespec *timebound);

struct timespec* getNanos(void);

long calculateNanos(struct timespec *time);

struct timespec* calculateTimebound(long timeout);
#endif // UTIL_H


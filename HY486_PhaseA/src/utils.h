#ifndef UTIL_H
#define UTIL_H

#include <pthread.h>
#include <errno.h>

#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
               do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define LEN_TOKENS 128

pthread_mutex_t initThreadsLock;

void usage(void);

void tokenize(char **tokens, int *asint, char *s); /*tokenization of input arguments*/

#endif // UTIL_H


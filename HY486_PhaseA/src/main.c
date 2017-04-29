/* 
 * File:   main.c
 * Author: Tasos198
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

#include "utils.h"
#include "client.h"
#include "updater.h"
#include "stack.h"
#include "list.h"

int main(int argc, char** argv) {
    int opt;
    int clients = 0;
    int updaters = 0;
    char* file = NULL;
    int numThreads;
    /* A very easy way to parse command line arguments */
    while ((opt = getopt(argc, argv, "c:u:f:")) != -1) {
        switch (opt) {
            case 'c':
                clients = atoi(optarg);
                break;
            case 'u':
                updaters = atoi(optarg);
                break;
            case 'f':
                file = strdup(optarg);
                break;
            default:
                usage();
                exit(EXIT_FAILURE);
        }
    }
    if (clients > 0 && updaters > 0 && file != NULL) {
        numThreads = clients + updaters;
        int c = -1;
        int u = -1;
        int status, i;
        pthread_t threads[numThreads];

        initMutex(&initThreadsLock); //located src/utils

        initStack();
        initList();
        initUpdaters();
        initClients(file, clients);

        while (c < (clients - 1) || u < (updaters - 1)) {
            if (c < (clients - 1)) {
                //entered on critical region
                lock(&initThreadsLock);
                ++c;
                //create client thread, on function we unlock mutex
                if ((status = pthread_create(&threads[c], NULL, (void*) clientLogic, (void *) &c)) != 0) {
                    handle_error_en(status, "pthread_create");
                }
            }
            if (u < (updaters - 1)) {
                //entered on critical region
                lock(&initThreadsLock);
                ++u;
                //create updater thread, on function we unlock mutex
                if ((status = pthread_create(&threads[clients + u], NULL, (void*) updaterLogic, (void *) &u)) != 0) {
                    handle_error_en(status, "pthread_create");
                }
            }
        }
        for (i = 0; i < clients; i++) {
            pthread_join(threads[i], NULL);
        }
        clientsDone = 1;

        for (i = clients; i < clients + updaters; i++) {
            pthread_join(threads[i], NULL);
        }

        //printStack();
        printList();
        destroyMutex(&initThreadsLock); //located src/utils
        cleanClient();
        cleanUpdaters();
        cleanStack();
        cleanList();
    } else {
        usage();
        return EXIT_FAILURE;
    }
    return (EXIT_SUCCESS);
}
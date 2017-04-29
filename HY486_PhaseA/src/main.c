/* 
 * File:   main.c
 * Author: Tasos198
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "utils.h"
#include "stack.h"
#include "client.h"
#include "updater.h"

int main(int argc, char** argv) {
    int opt;
    int clients = 0;
    int updaters = 0;
    filepath = NULL;
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
                filepath = strdup(optarg);
                break;
            default:
                usage();
                exit(EXIT_FAILURE);
        }
    }
    if (clients > 0 && updaters > 0 && filepath != NULL) {
        numThreads = clients + updaters;
        int c = -1;
        int u = -1;
        int status, i;
        pthread_t threads[numThreads];

        status = pthread_mutex_init(&initThreadsLock, NULL);
        if (status != 0) {
            handle_error_en(status, "pthread_mutex_init");
        }

        status = pthread_barrier_init(&clientBarrier, NULL, clients);
        if (status != 0) {
            handle_error_en(status, "pthread_barrier_init");
        }

        initStack();
        total_operations = 0;
        clientsDone = 0;
        while (c < (clients - 1) || u < (updaters - 1)) {
            if (c < (clients - 1)) {
                //entered on critical region
                if ((status = pthread_mutex_lock(&initThreadsLock)) != 0) {
                    handle_error_en(status, "pthread_mutex_lock");
                }
                ++c;
                //create client thread, on function we unlock mutex
                if ((status = pthread_create(&threads[c], NULL, (void*) clientLogic, (void *) &c)) != 0) {
                    handle_error_en(status, "pthread_create");
                }
            }
            if (u < (updaters - 1)) {
                //entered on critical region
                if ((status = pthread_mutex_lock(&initThreadsLock)) != 0) {
                    handle_error_en(status, "pthread_mutex_lock");
                }
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
        printf("clients done\n");

        for (i = clients; i < clients + updaters; i++) {
            pthread_join(threads[i], NULL);
        }
        printf("updaters done\n");

        printStack();
        
        cleanClient();
        cleanStack();
    } else {
        usage();
        return EXIT_FAILURE;
    }
    return (EXIT_SUCCESS);
}
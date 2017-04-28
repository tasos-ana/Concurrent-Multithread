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
#include "client.h"
#include "updater.h"

int main(int argc, char** argv) {
    int opt;
    int clients = 0;
    int updaters = 0;
    filepath = NULL;

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
        int c = -1;
        int u = -1;
        int status;
        pthread_t pth;

        status = pthread_mutex_init(&initThreadsLock, NULL);
        if (status != 0) {
            handle_error_en(status, "pthread_mutex_init");
        }

        while (c < (clients - 1) || u < (updaters - 1)) {
            if (c < (clients - 1)) {
                //entered on critical region
                if ((status = pthread_mutex_lock(&initThreadsLock)) != 0) {
                    handle_error_en(status, "pthread_mutex_lock");
                }
                ++c;
                //create client thread, on function we unlock mutex
                if ((status = pthread_create(&pth, NULL, (void*) clientLogic, (void *) &c)) != 0) {
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
                if ((status = pthread_create(&pth, NULL, (void*) updaterLogic, (void *) &u)) != 0) {
                    handle_error_en(status, "pthread_create");
                }
            }
        }
        //lock for last thread so we didn't exit from function and i lost.
        if ((status = pthread_mutex_lock(&initThreadsLock)) != 0) {
            handle_error_en(status, "pthread_mutex_lock");
        }
        sleep(100);
        free(filepath);
    } else {
        usage();
        return EXIT_FAILURE;
    }
    return (EXIT_SUCCESS);
}
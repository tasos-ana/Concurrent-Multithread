/* 
 * File:   main.c
 * Author: Tasos198
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//#include "client.h"
//#include "updater.h"
void usage();

int main(int argc, char** argv) {
    int opt;
    int clients = 0;
    int updaters = 0;
    char *file = NULL;

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
        printf("updater: %d \n client: %d\n file: %s\n", updaters, clients, file);
        free(file);
    } else {
        usage();
        return EXIT_FAILURE;
    }
    return (EXIT_SUCCESS);
}

void usage() {
    printf("Usage: prog -c clientNum -u updaterNum -f file"
            "Options:\n"
            "   -c <int>            Set the clients thread number.\n"
            "   -u <int>            Set the updater thread number.\n"
            "   -f <string>         Set -f option specifies the file path of the input.\n"
            "   -h                  prints this help\n");
}


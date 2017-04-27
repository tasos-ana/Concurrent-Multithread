/* 
 * File:   main.c
 * Author: Tasos198
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "client.h"
#include "updater.h"

int main(int argc, char** argv) {
    if (argc != 4) {
        fprintf(stderr, "Wrong arguments! Usage: [program name] [client Number] [updater Number] [input file path]\n");
        return (EXIT_FAILURE);
    } else {
        int clients = atoi(argv[1]);
        int updaters = atoi(argv[2]);
        char* file = argv[3];
        if (clients < 0) {
            fprintf(stderr, "Client number cant be negative\n");
            return (EXIT_FAILURE);
        }
        if (updaters < 0) {
            fprintf(stderr, "Updater number cant be negative\n");
            return (EXIT_FAILURE);
        }
        initClients(clients, file);
        initUpdaters(updaters, file);
    }
    return (EXIT_SUCCESS);
}


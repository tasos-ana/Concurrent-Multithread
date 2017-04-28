#include <stdio.h>

#include "utils.h"

void usage(void) {
    printf("Usage: prog -c clientNum -u updaterNum -f file"
            "Options:\n"
            "   -c <int>            Set the clients thread number.\n"
            "   -u <int>            Set the updater thread number.\n"
            "   -f <string>         Set -f option specifies the file path of the input.\n"
            "   -h                  prints this help\n");
}
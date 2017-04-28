#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"

void usage(void) {
    printf("Usage: prog -c clientNum -u updaterNum -f file"
            "Options:\n"
            "   -c <int>            Set the clients thread number.\n"
            "   -u <int>            Set the updater thread number.\n"
            "   -f <string>         Set -f option specifies the file path of the input.\n"
            "   -h                  prints this help\n");
}

void tokenize(char *s) { /*tokenization of input arguments*/
	char *p, *last;
	int i = 0;
	for ((p = strtok_r(s, " ", &last)); p;
	    (p = strtok_r(NULL, " ", &last))) {
		if (i < LEN(tokens) - 1) {
			tokens[i] = p;
			asint[i] = atoi(p);
			i++;
		}
	}
	tokens[i] = NULL;
}
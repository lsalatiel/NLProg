#include "libraries.h"

void DefaultTextColour() {
    printf("\033[0m");
}

void RedTextColour() {
    printf("\033[1;31m");
}

void CheckDataFilesPath(int argc) {
    if (argc != 3) {
        RedTextColour();
        printf("ERROR: Invalid number of arguments.\n");
        DefaultTextColour();
        exit(1);
    }
}

void resetString(char* name) {
    for(size_t i = 0; i < strlen(name); i++) {
        name[i] = '\0';
    }
}

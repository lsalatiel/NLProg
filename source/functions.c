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

void PrintFileError() {
    RedTextColour();
    printf("ERROR: Could not open the file.\n");
    DefaultTextColour();
}

void FreeAndNull(void* pointer) {
    free(pointer);
    pointer = NULL;
}

bool EndOfFile(char character) {
    if (character == '\0' || character == '\n' || character == '\r') {
        return true;
    } else {
        return false;
    }
}

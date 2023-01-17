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

float CalculateTf_idf(int frequency, int document_quantity, int word_appearance) {
    float tf = frequency;

    float x = (1 + document_quantity) / (1 + word_appearance);
    float idf = log(x) + 1;

    return tf * idf;
}

void ClearTerminal() {
    while (system("clear") == 0) {
        break;
    }
}

int GetValidIntegerInput(int min_range, int max_range) {
    while (ONLINE) {
        char* buffer = NULL;
        size_t len = 0;
        ssize_t read;

        read = getline(&buffer, &len, stdin);
        if (read != -1) {
            buffer[read - 1] = '\0';

            if (buffer[0] >= '0' && buffer[0] <= '9') {
                int input = atoi(buffer);

                if (input >= min_range && input <= max_range) {
                    FreeAndNull(buffer);
                    DefaultTextColour();
                    ClearTerminal();
                    return input;
                }
            }
        }

        RedTextColour();
        printf("• ERROR: Invalid option. Try again: ");
    }
}

int SetUpMainMenu() {
    printf("1 | Search news\n");
    printf("2 | Sort news\n");
    printf("3 | Word relatory\n");
    printf("4 | Document relatory\n");
    printf("5 | Quit program\n\n");
    printf("Enter an option: ");

    return GetValidIntegerInput(1, 5);
}

char** GetUserSearchInput(int* query_size) {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    read = getline(&line, &len, stdin);

    if (read == -1) {
        printf("Error reading input\n");
        return NULL;
    }

    char** res = NULL;
    char* p = strtok(line, " ");
    int n_spaces = 0;

    while (p) {
        res = realloc(res, sizeof(char*) * ++n_spaces);
        if (res == NULL) {
            printf("Error allocating memory\n");
            return NULL;
        }
        res[n_spaces - 1] = strdup(p);
        p = strtok(NULL, " ");
    }

    FreeAndNull(line);
    *query_size = n_spaces;
    return res;
}
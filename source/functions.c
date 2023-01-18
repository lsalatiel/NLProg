#include "libraries.h"

void BoldText() {
    printf("\e[1m");
}

void DefaultText() {
    printf("\033[0m");
}

void RedText() {
    printf("\033[1;31m");
}

void CheckDataFilesPath(int argc) {
    if (argc != 3) {
        RedText();
        printf("• ERROR: Invalid number of command line arguments.\n");
        DefaultText();
        exit(1);
    }
}

void PrintFileError() {
    RedText();
    printf("• ERROR: File not found.\n");
    DefaultText();
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
                    ClearTerminal();
                    DefaultText();
                    return input;
                }
            }
        }

        RedText();
        printf("• ERROR: Invalid option. Try again: ");
    }
}

int SetUpMainMenu() {
    PrintArtMenu();
    BoldText();
    printf("\n• Enter an option: ");
    DefaultText();

    return GetValidIntegerInput(1, 5);
}

char** GetUserSearchInput(int* query_size) {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    read = getline(&line, &len, stdin);

    if (read == -1) {
        RedText();
        printf("• ERROR: Invalid search. Try again: ");
        DefaultText();
        return NULL;
    }

    line[read - 1] = '\0';
    char** result = NULL;
    char* token = strtok(line, " ");
    int spaces = 0;

    while (token) {
        result = realloc(result, sizeof(char*) * ++spaces);

        if (result == NULL) {
            RedText();
            printf("• ERROR: Invalid search. Try again: ");
            DefaultText();
            return NULL;
        }

        result[spaces - 1] = strdup(token);
        token = strtok(NULL, " ");
    }

    FreeAndNull(line);

    *query_size = spaces;
    return result;
}

void ResetUserSearchInput(char** input, int* input_size) {
    for (int x = 0; x < *input_size; x++) {
        FreeAndNull(input[x]);
    }

    FreeAndNull(input_size);
    FreeAndNull(input);
}

void PrintArtMenu() {
    BoldText();
    printf(" ╔═══╗   ┌─┐┌─┐┌─┐┬─┐┌─┐┬ ┬  ┌┐┌┌─┐┬ ┬┌─┐\n");
    printf(" █ 1 █   └─┐├┤ ├─┤├┬┘│  ├─┤  │││├┤ │││└─┐\n");
    printf(" ╚═══╝   └─┘└─┘┴ ┴┴└─└─┘┴ ┴  ┘└┘└─┘└┴┘└─┘\n");
    printf(" ╔═══╗   ┌─┐┌─┐┬─┐┌┬┐  ┌┐┌┌─┐┬ ┬┌─┐\n");
    printf(" █ 2 █   └─┐│ │├┬┘ │   │││├┤ │││└─┐\n");
    printf(" ╚═══╝   └─┘└─┘┴└─ ┴   ┘└┘└─┘└┴┘└─┘\n");
    printf(" ╔═══╗   ┬ ┬┌─┐┬─┐┌┬┐  ┬─┐┌─┐┬  ┌─┐┌┬┐┌─┐┬─┐┬ ┬\n");
    printf(" █ 3 █   ││││ │├┬┘ ││  ├┬┘├┤ │  ├─┤ │ │ │├┬┘└┬┘\n");
    printf(" ╚═══╝   └┴┘└─┘┴└──┴┘  ┴└─└─┘┴─┘┴ ┴ ┴ └─┘┴└─ ┴\n");
    printf(" ╔═══╗   ┌┬┐┌─┐┌─┐┬ ┬┌┬┐┌─┐┌┐┌┌┬┐  ┬─┐┌─┐┬  ┌─┐┌┬┐┌─┐┬─┐┬ ┬\n");
    printf(" █ 4 █    │││ ││  │ ││││├┤ │││ │   ├┬┘├┤ │  ├─┤ │ │ │├┬┘└┬┘\n");
    printf(" ╚═══╝   ─┴┘└─┘└─┘└─┘┴ ┴└─┘┘└┘ ┴   ┴└─└─┘┴─┘┴ ┴ ┴ └─┘┴└─ ┴\n");
    printf(" ╔═══╗   ┬  ┌─┐┌─┐┬  ┬┌─┐  ┌─┐┬─┐┌─┐┌─┐┬─┐┌─┐┌┬┐\n");
    printf(" █ 5 █   │  ├┤ ├─┤└┐┌┘├┤   ├─┘├┬┘│ ││ ┬├┬┘├─┤│││\n");
    printf(" ╚═══╝   ┴─┘└─┘┴ ┴ └┘ └─┘  ┴  ┴└─└─┘└─┘┴└─┴ ┴┴ ┴\n");
    DefaultText();
}
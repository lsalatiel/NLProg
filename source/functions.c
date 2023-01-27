#include "libraries.h"

void CheckDataFilesPath(int argc) {
    ClearTerminal();
    if (argc != 3) {
        printf(BOLD RED "ERROR: Invalid number of command line arguments.\n" DEFAULT);

        exit(1);
    }
}

void PrintFileError() {
    printf(BOLD RED "ERROR: File not found.\n" DEFAULT);
}

void FreeAndNull(void* pointer) {
    free(pointer);
    pointer = NULL;
}

bool EndOfFile(char character) {
    if (character == '\0' || character == '\n' || character == '\r' || character == ' ' || character == '\t') {
        return true;
    } else {
        return false;
    }
}

float CalculateTFIDF(int frequency, int documentQuantity, int wordAppearance) {
    float tf = frequency;

    float x = (1 + documentQuantity) / (1 + wordAppearance);
    float idf = log(x) + 1;

    return tf * idf;
}

void ClearTerminal() {
    while (system("clear") == 0) {
        break;
    }
}

int GetValidIntegerInput(int minimumRange, int maximumRange) {
    while (ONLINE) {
        char* buffer = NULL;
        size_t len = 0;
        ssize_t read;

        read = getline(&buffer, &len, stdin);
        if (read != -1) {
            buffer[read - 1] = '\0';

            if (buffer[0] >= '0' && buffer[0] <= '9') {
                int input = atoi(buffer);

                if (input >= minimumRange && input <= maximumRange) {
                    FreeAndNull(buffer);
                    ClearTerminal();
                    return input;
                }
            }
        }

        printf(BOLD RED "• ERROR: Invalid option. Try again: " DEFAULT);
    }
}

int SetUpMainMenu() {
    PrintArtMenu();

    printf(BOLD "\n• Enter an option: " DEFAULT);

    return GetValidIntegerInput(1, 5);
}

char** GetUserSentenceInput(int* querySize) {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    read = getline(&line, &len, stdin);

    if (read == -1) {
        printf(BOLD RED "• ERROR: Invalid search. Try again: " DEFAULT);

        return NULL;
    }

    line[read - 1] = '\0';
    char** result = NULL;
    char* token = strtok(line, " ");
    int spaces = 0;

    while (token) {
        result = realloc(result, sizeof(char*) * ++spaces);

        if (result == NULL) {
            printf(BOLD RED "• ERROR: Invalid search. Try again: " DEFAULT);

            return NULL;
        }

        result[spaces - 1] = strdup(token);
        token = strtok(NULL, " ");
    }

    *querySize = spaces;
    FreeAndNull(line);
    printf("\n");

    return result;
}

void ResetUserSearchInput(char** input, int* inputSize) {
    for (int x = 0; x < *inputSize; x++) {
        FreeAndNull(input[x]);
    }

    FreeAndNull(inputSize);
    FreeAndNull(input);
}

char* GetUserWordInput() {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    read = getline(&line, &len, stdin);

    if (read == -1) {
        printf(BOLD RED "• ERROR: Invalid search. Try again: " DEFAULT);

        return NULL;
    }

    line[read - 1] = '\0';
    printf("\n");

    return line;
}

void PrintArtMenu() {
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
}

char* IsItTrainOrTestFile(char* argv) {
    char* argvCopy = strdup(argv);
    size_t argvLen = strlen(argvCopy);
    char testXtrain = argvCopy[argvLen - 5];

    if (testXtrain == 't')
        argvCopy[argvLen - 8] = '\0';
    else if (testXtrain == 'n')
        argvCopy[argvLen - 9] = '\0';

    return argvCopy;
}
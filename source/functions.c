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

void GreenText() {
    printf("\033[1;32m");
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
                    DefaultText();
                    return input;
                }
            }
        }

        RedText();
        printf("• ERROR: Invalid option. Try again: ");
        FreeAndNull(buffer);
    }
}

int SetUpMainMenu() {
    PrintArtMenu();
    BoldText();
    printf("\n• Enter an option: ");
    DefaultText();

    return GetValidIntegerInput(1, 5);
}

char** GetUserSentenceInput(int* querySize) {
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
        RedText();
        printf("• ERROR: Invalid search. Try again: ");
        DefaultText();
        return NULL;
    }

    line[read - 1] = '\0';
    printf("\n");

    return line;
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

int CompareFloats(const void* a, const void* b) {
    return *(float*)b - *(float*)a;
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
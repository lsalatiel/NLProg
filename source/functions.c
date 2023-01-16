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

    float tf_idf = tf * idf;

    return tf_idf;
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
        printf("• ERRO: Opção inválida. Tente novamente: ");
    }
}

int SetUpMainMenu() {
    printf("1 | Buscar notícias\n");
    printf("2 | Classificar notícias\n");
    printf("3 | Relatório de palavra\n");
    printf("4 | Relatório de documentos\n");
    printf("5 | Sair do programa\n\n");
    printf("Digite a opção desejada: ");

    return GetValidIntegerInput(1, 5);
}
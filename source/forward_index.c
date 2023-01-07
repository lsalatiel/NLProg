#include "libraries.h"

struct ForwardIndex {
    int index;
    char* name;
    char* class;
    DocumentInfo** info;
    int info_size;
    int info_alloc;
};

ForwardIndex* AllocateDocuments() {
    return calloc(sizeof(ForwardIndex), 1);
}

void FreeDocuments(ForwardIndex* documents) {
    FreeAndNull(documents->name);
    FreeAndNull(documents->class);
    FreeAndNull(documents);
}

ForwardIndex** ReadDocuments(ForwardIndex** documents, FILE* train, int* documents_size, int* documents_alloc) {
    char* buffer = malloc(1024 * sizeof(char));

    for (int x = 0; fgets(buffer, 1024, train) && !EndOfFile(buffer[0]); x++) {
        documents[x]->index = x;
        documents[x]->name = strdup(strtok(buffer, " "));
        documents[x]->class = strdup(strtok(NULL, "\n"));
    }

    FreeAndNull(buffer);

    return documents;
}
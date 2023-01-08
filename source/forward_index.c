#include "libraries.h"

struct ForwardIndex {
    int index;
    char* name;
    char* class;
    DocumentInfo** info;
    int* info_size;
    int* info_alloc;
};

ForwardIndex* AllocateDocuments() {
    ForwardIndex* document = NULL;

    document = calloc(sizeof(ForwardIndex), 1);
    document->info = malloc(STARTER_ALLOC * sizeof(DocumentInfo*));
    document->info_size = malloc(sizeof(int));
    document->info_alloc = malloc(sizeof(int));
    *document->info_size = 0;
    *document->info_alloc = STARTER_ALLOC;

    for (int x = 0; x < STARTER_ALLOC; x++) {
        document->info[x] = AllocateDocumentsInfo();
    }

    return document;
}

void FreeDocuments(ForwardIndex* documents) {
    for (int x = 0; x < *documents->info_alloc; x++) {
        FreeDocumentsInfo(documents->info[x]);
    }

    FreeAndNull(documents->name);
    FreeAndNull(documents->class);
    FreeAndNull(documents->info);
    FreeAndNull(documents->info_size);
    FreeAndNull(documents->info_alloc);
    FreeAndNull(documents);
}

ForwardIndex** ReadDocuments(ForwardIndex** documents, FILE* train, int* documents_size, int* documents_alloc) {
    char* buffer = malloc(BUFFER_SIZE * sizeof(char));

    for (int x = 0; fgets(buffer, BUFFER_SIZE, train) && !EndOfFile(buffer[0]); x++) {
        if (x == *documents_alloc) {
            *documents_alloc *= 2;
            documents = ReallocDocuments(documents, documents_alloc);
        }

        documents[x]->index = x;
        documents[x]->name = strdup(strtok(buffer, " "));
        documents[x]->class = strdup(strtok(NULL, "\n"));
    }

    FreeAndNull(buffer);

    return documents;
}

ForwardIndex** ReallocDocuments(ForwardIndex** documents, int* documents_alloc) {
    ForwardIndex** new = NULL;
    new = realloc(documents, *documents_alloc * sizeof(ForwardIndex*));
    documents = new;

    for (int x = *documents_alloc / 2; x < *documents_alloc; x++) {
        documents[x] = AllocateDocuments();
    }

    return documents;
}

char* GetFileName(ForwardIndex* document) {
    return document->name;
}
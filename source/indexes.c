#include "libraries.h"

struct Indexes {
    ForwardIndex** documents;
    int* documents_size;
    int* documents_alloc;
    InvertedIndex** words;
    int* words_size;
    int* words_alloc;
};

Indexes* ReadTrainFile(Indexes* indexes, char** argv) {
    FILE* train = fopen(argv[1], "r");
    if (!train) {
        PrintFileError();
        exit(1);
    }

    fclose(train);

    return indexes;
}

Indexes* AllocateIndexes(Indexes* indexes) {
    indexes = malloc(sizeof(Indexes));

    indexes->documents = malloc(STARTER_ALLOC * sizeof(ForwardIndex*));
    indexes->documents_size = malloc(sizeof(int));
    indexes->documents_alloc = malloc(sizeof(int));
    *indexes->documents_size = 0;
    *indexes->documents_alloc = STARTER_ALLOC;

    indexes->words = malloc(STARTER_ALLOC * sizeof(InvertedIndex*));
    indexes->words_size = malloc(sizeof(int));
    indexes->words_alloc = malloc(sizeof(int));
    *indexes->words_size = 0;
    *indexes->words_alloc = STARTER_ALLOC;

    for (int x = 0; x < STARTER_ALLOC; x++) {
        indexes->documents[x] = AllocateDocuments();
        indexes->words[x] = AllocateWords();
    }

    return indexes;
}

void FreeIndexes(Indexes* indexes) {
    for (int x = 0; x < *indexes->documents_alloc; x++) {
        FreeDocuments(indexes->documents[x]);
    }

    for (int x = 0; x < *indexes->words_alloc; x++) {
        FreeWords(indexes->words[x]);
    }

    FreeAndNull(indexes->documents);
    FreeAndNull(indexes->documents_size);
    FreeAndNull(indexes->documents_alloc);
    FreeAndNull(indexes->words);
    FreeAndNull(indexes->words_size);
    FreeAndNull(indexes->words_alloc);
    FreeAndNull(indexes);
}
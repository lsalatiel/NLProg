#include "libraries.h"

struct Indexes {
    ForwardIndex** documents;
    int* documents_size;
    int* documents_alloc;
    InvertedIndex** words;
    int* words_size;
    int* words_alloc;
};

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

Indexes* ReadTrainFile(Indexes* indexes, char** argv) {
    FILE* train = fopen(argv[1], "r");
    if (!train) {
        FreeIndexes(indexes);
        PrintFileError();
        exit(1);
    }

    indexes->documents = ReadDocuments(indexes->documents, train, indexes->documents_size, indexes->documents_alloc);
    // indexes->words =

    fclose(train);

    return indexes;
}

void FreeIndexes(Indexes* indexes) {
    for (int x = 0; x < *indexes->documents_alloc; x++) {
        FreeDocuments(indexes->documents[x]);
    }

    for (int x = 0; x < *indexes->words_alloc; x++) {
        FreeWord(indexes->words[x]);
    }

    FreeAndNull(indexes->documents);
    FreeAndNull(indexes->documents_size);
    FreeAndNull(indexes->documents_alloc);
    FreeAndNull(indexes->words);
    FreeAndNull(indexes->words_size);
    FreeAndNull(indexes->words_alloc);
    FreeAndNull(indexes);
}

Indexes* ReadInfo(Indexes* indexes) {
    FILE* file;

    //char* file_name = NULL;
    char file_name[200];
    char path[300];

    for(int i = 0; i < *indexes->documents_size; i++) {
        //file_name = GetFileName(indexes->documents[i]);
        strcpy(file_name, GetFileName(indexes->documents[i]));

        sprintf(path, "datasets/tiny/%s", file_name);

        file = fopen(path, "r");

        if(file == NULL) {
            continue;
        }

        indexes = CreateIndexesFromFile(indexes, file, i);

        fclose(file);
    }

    return indexes;
}

Indexes* CreateIndexesFromFile(Indexes* indexes, FILE* file, int document_index) {
    //char* word;
    char word[200];
    int word_index = 0;

    if(file == NULL) {
        return NULL;
    }

    while(!feof(file)) {
        if(*indexes->words_size == *indexes->words_alloc) {
            *indexes->words_alloc *= 2;
            indexes->words = ReallocWords(indexes->words, indexes->words_alloc);
        }

        fscanf(file, "%s", word);
        // as funcoes de baixo (fora a getwordindex(euacho)) nao estao completas
        
        word_index = GetWordIndex(indexes->words, word, *indexes->words_size); // returns -1 if word does exist
        if(word_index != -1) {
            indexes->words = AddDocumentFrequencyToInvertedIndex(indexes->words, word_index, document_index);
            continue;
        }
        // allocates space for the word info array (only for new words)
        AllocateWordInfoArray(indexes->words, *indexes->words_size, *indexes->documents_size); // poderia ser documents_size - document_index pra alocar menos espaco
        indexes->words = StoreWordInvertedIndex(indexes->words, word, *indexes->words_size, document_index);
        (*indexes->words_size)++;
    }

    return indexes;
}

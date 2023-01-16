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
        indexes->documents[x] = AllocateDocument();
        indexes->words[x] = AllocateWord();
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

    fclose(train);

    return indexes;
}

void FreeIndexes(Indexes* indexes) {
    for (int x = 0; x < *indexes->documents_alloc; x++) {
        FreeDocument(indexes->documents[x]);
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

    char* file_name;
    char path[MAX_FILE_PATH_LENGTH];

    for (int i = 0; i < *indexes->documents_size; i++) {
        file_name = GetFileName(indexes->documents[i]);
        // strcpy(file_name, GetFileName(indexes->documents[i]));

        sprintf(path, "datasets/tiny/%s", file_name);

        file = fopen(path, "r");

        if (file == NULL) {
            continue;
        }

        indexes = CreateIndexesFromFile(indexes, file, i);

        fclose(file);
    }

    indexes = StoreTf_idfFromIndexes(indexes);

    return indexes;
}

Indexes* CreateIndexesFromFile(Indexes* indexes, FILE* file, int document_index) {
    char word[1000];
    word[0] = '\0';
    int word_index = 0;

    if (file == NULL) {
        return NULL;
    }

    while (!feof(file)) {
        if (*indexes->words_size == *indexes->words_alloc) {
            *indexes->words_alloc *= 2;
            indexes->words = ReallocWords(indexes->words, indexes->words_alloc);
        }

        word[0] = '\0';

        fscanf(file, "%s", word);

        if (word[0] == '\0' || word[0] == ' ' || word[0] == '\n' || word[0] == '\t') {
            continue;
        }

        word_index = GetWordIndex(indexes->words, word, *indexes->words_size);  // returns -1 if word does not exist
        if (word_index != -1) {
            // se a palavra nao eh nova ela pode ter aparecido no documento ou nao
            if (WordInDocument(indexes->words[word_index], document_index == true)) {
                indexes->documents[document_index] = AddWordFrequencyToForwardIndex(indexes->documents[document_index], word_index);
            } else {
                indexes->documents[document_index] = StoreWordInfoForwardIndex(indexes->documents[document_index], word_index);
            }

            indexes->words = AddDocumentFrequencyToInvertedIndex(indexes->words, word_index, document_index);
            continue;
        }
        // allocates space for the word info array (only for new words)
        indexes->words = AllocateWordInfoArray(indexes->words, *indexes->words_size);
        indexes->words = StoreWordInvertedIndex(indexes->words, word, *indexes->words_size, document_index);
        // p essa funcao o *indexes->words_size vai servir como indice da word
        indexes->documents[document_index] = StoreWordInfoForwardIndex(indexes->documents[document_index], *indexes->words_size);
        (*indexes->words_size)++;
    }

    return indexes;
}

Indexes* StoreTf_idfFromIndexes(Indexes* indexes) {
    int word_appearance = 0;

    for (int i = 0; i < *indexes->words_size; i++) {
        indexes->words[i] = StoreTf_idfFromfWord(indexes->words[i], *indexes->documents_size);

        word_appearance = GetWordInfoSize(indexes->words[i]);
        indexes->documents = StoreTf_idfFromDocuments(indexes->documents, i, *indexes->documents_size, word_appearance);
    }

    return indexes;
}

void SaveIndexesInBinary(Indexes* indexes, char* argv) {
    int argv_size = 0;
    argv_size = strlen(argv);
    char* file_name = NULL;
    file_name = malloc(sizeof(char) * (argv_size + 8));
    strcpy(file_name, "binary/");
    strcat(file_name, argv);

    FILE* file = fopen(file_name, "wb");
    FreeAndNull(file_name);

    if (file == NULL) {
        printf("ERROR: could not create binary file.\n");
        return;
    }

    // writing documents
    fwrite(indexes->documents_size, 1, sizeof(int), file);
    fwrite(indexes->documents_alloc, 1, sizeof(int), file);

    for (int i = 0; i < *indexes->documents_size; i++) {
        SaveForwardIndexInBinary(indexes->documents[i], file);
    }

    // writing words
    fwrite(indexes->words_size, 1, sizeof(int), file);
    fwrite(indexes->words_alloc, 1, sizeof(int), file);

    for (int i = 0; i < *indexes->words_size; i++) {
        SaveInvertedIndexInBinary(indexes->words[i], file);
    }

    fclose(file);
}
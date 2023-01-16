#include "libraries.h"

struct Indexes {
    ForwardIndex** documents;
    int* documents_size;
    int* documents_alloc;
    InvertedIndex** words;
    int* words_size;
    int* words_alloc;
};

Indexes* AllocateIndexes() {
    Indexes* indexes = NULL;
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

void WriteIndexesInBinaryFile(Indexes* indexes, char* file_name) {
    char* binary_file_name = NULL;
    binary_file_name = malloc(sizeof(char) * (strlen(file_name) + 8));
    strcpy(binary_file_name, "binary/");
    strcat(binary_file_name, file_name);

    FILE* file = fopen(binary_file_name, "wb");
    FreeAndNull(binary_file_name);

    if (file == NULL) {
        printf("ERROR: could not create binary file.\n");
        return;
    }

    // writing documents
    fwrite(indexes->documents_size, sizeof(int), 1, file);
    fwrite(indexes->documents_alloc, sizeof(int), 1, file);

    for (int i = 0; i < *indexes->documents_size; i++) {
        WriteForwardIndexInBinaryFile(indexes->documents[i], file);
    }

    // writing words
    fwrite(indexes->words_size, sizeof(int), 1, file);
    fwrite(indexes->words_alloc, sizeof(int), 1, file);

    for (int i = 0; i < *indexes->words_size; i++) {
        WriteInvertedIndexInBinaryFile(indexes->words[i], file);
    }

    fclose(file);
}

Indexes* ReadIndexesFromBinaryFile(Indexes* indexes, char* file_name) {
    char* binary_file_name = NULL;
    binary_file_name = malloc(sizeof(char) * (strlen(file_name) + 8));
    strcpy(binary_file_name, "binary/");
    strcat(binary_file_name, file_name);

    FILE* file = fopen(binary_file_name, "rb");
    FreeAndNull(binary_file_name);

    if (file == NULL) {
        printf("ERROR: could not open binary file.\n");
        return NULL;
    }

    // reading documents
    fread(indexes->documents_size, sizeof(int), 1, file);
    fread(indexes->documents_alloc, sizeof(int), 1, file);

    int alloc = STARTER_ALLOC;
    for (int i = 0; i < *indexes->documents_size; i++) {
        if (i == alloc) {
            alloc *= 2;
            indexes->documents = ReallocDocuments(indexes->documents, &alloc);
        }

        ReadForwardIndexFromBinaryFile(indexes->documents[i], file);
    }

    // reading words
    fread(indexes->words_size, sizeof(int), 1, file);
    fread(indexes->words_alloc, sizeof(int), 1, file);

    alloc = STARTER_ALLOC;
    for (int i = 0; i < *indexes->words_size; i++) {
        if (i == alloc) {
            alloc *= 2;
            indexes->words = ReallocWords(indexes->words, &alloc);
        }

        ReadInvertedIndexFromBinaryFile(indexes->words[i], file);
    }

    fclose(file);

    return indexes;
}
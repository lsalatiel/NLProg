#include "libraries.h"

struct Indexes {
    ForwardIndex** documents;
    int* documentsSize;
    int* documentsAlloc;
    InvertedIndex** words;
    int* wordsSize;
    int* wordsAlloc;
};

Indexes* AllocateIndexes() {
    Indexes* indexes = NULL;
    indexes = malloc(sizeof(Indexes));

    indexes->documents = malloc(STARTER_ALLOC * sizeof(ForwardIndex*));
    indexes->documentsSize = calloc(sizeof(int), 1);
    indexes->documentsAlloc = malloc(sizeof(int));
    *indexes->documentsAlloc = STARTER_ALLOC;

    indexes->words = malloc(STARTER_ALLOC * sizeof(InvertedIndex*));
    indexes->wordsSize = calloc(sizeof(int), 1);
    indexes->wordsAlloc = malloc(sizeof(int));
    *indexes->wordsAlloc = STARTER_ALLOC;

    for (int x = 0; x < STARTER_ALLOC; x++) {
        indexes->documents[x] = AllocDocument();
        indexes->words[x] = AllocWord();
    }

    return indexes;
}

Indexes* ReadTrainFile(Indexes* indexes, char** argv) {
    FILE* train = fopen(argv[1], "r");
    if (!train) {
        FreeAndNull(indexes);
        PrintFileError();
        exit(1);
    }

    indexes->documents = ReadDocuments(indexes->documents, train, indexes->documentsSize, indexes->documentsAlloc);

    fclose(train);

    return indexes;
}

void FreeIndexes(Indexes* indexes) {
    for (int x = 0; x < *indexes->documentsAlloc; x++) {
        FreeDocument(indexes->documents[x]);
    }

    for (int x = 0; x < *indexes->wordsAlloc; x++) {
        FreeWord(indexes->words[x]);
    }

    FreeAndNull(indexes->documents);
    FreeAndNull(indexes->documentsSize);
    FreeAndNull(indexes->documentsAlloc);
    FreeAndNull(indexes->words);
    FreeAndNull(indexes->wordsSize);
    FreeAndNull(indexes->wordsAlloc);
    FreeAndNull(indexes);
}

Indexes* ReadInfo(Indexes* indexes) {
    FILE* file;

    char* fileName;
    char path[MAX_FILE_PATH_LENGTH];

    for (int i = 0; i < *indexes->documentsSize; i++) {
        fileName = GetFileName(indexes->documents[i]);
        // strcpy(fileName, GetFileName(indexes->documents[i]));

        sprintf(path, "datasets/tiny/%s", fileName);

        file = fopen(path, "r");

        if (file == NULL) {
            continue;
        }

        indexes = CreateIndexesFromFile(indexes, file, i);

        fclose(file);
    }

    indexes = StoreTFIDFFromIndexes(indexes);

    return indexes;
}

Indexes* CreateIndexesFromFile(Indexes* indexes, FILE* file, int documentIndex) {
    char word[1000];
    word[0] = '\0';
    int wordIndex = 0;

    if (file == NULL) {
        return NULL;
    }

    while (!feof(file)) {
        if (*indexes->wordsSize == *indexes->wordsAlloc) {
            *indexes->wordsAlloc *= 2;
            indexes->words = ReallocWords(indexes->words, indexes->wordsAlloc);
        }

        word[0] = '\0';

        fscanf(file, "%s", word);

        if (EndOfFile(word[0])) {
            continue;
        }

        wordIndex = GetWordIndex(indexes->words, word, *indexes->wordsSize);  // returns -1 if word does not exist
        if (wordIndex != -1) {
            // se a palavra nao eh nova ela pode ter aparecido no documento ou nao
            if (WordInDocument(indexes->words[wordIndex], documentIndex == true)) {
                indexes->documents[documentIndex] = AddWordFrequencyToForwardIndex(indexes->documents[documentIndex], wordIndex);
            } else {
                indexes->documents[documentIndex] = StoreWordInfoForwardIndex(indexes->documents[documentIndex], wordIndex);
            }

            indexes->words = AddDocumentFrequencyToInvertedIndex(indexes->words, wordIndex, documentIndex);
            continue;
        }
        // allocates space for the word info array (only for new words)
        indexes->words = AllocWordInfoArray(indexes->words, *indexes->wordsSize);
        indexes->words = StoreWordInvertedIndex(indexes->words, word, *indexes->wordsSize, documentIndex);
        // p essa funcao o *indexes->wordsSize vai servir como indice da word
        indexes->documents[documentIndex] = StoreWordInfoForwardIndex(indexes->documents[documentIndex], *indexes->wordsSize);
        (*indexes->wordsSize)++;
    }

    return indexes;
}

Indexes* StoreTFIDFFromIndexes(Indexes* indexes) {
    int wordAppearance = 0;

    for (int i = 0; i < *indexes->wordsSize; i++) {
        indexes->words[i] = StoreTFIDFFromWord(indexes->words[i], *indexes->documentsSize);

        wordAppearance = GetWordInfoSize(indexes->words[i]);
        indexes->documents = StoreTFIDFFromDocuments(indexes->documents, i, *indexes->documentsSize, wordAppearance);
    }

    return indexes;
}

void WriteIndexesInBinaryFile(Indexes* indexes, char* fileName) {
    char* binaryFileName = NULL;
    binaryFileName = malloc(sizeof(char) * (strlen(fileName) + 8));
    strcpy(binaryFileName, "binary/");
    strcat(binaryFileName, fileName);

    FILE* file = fopen(binaryFileName, "wb");
    FreeAndNull(binaryFileName);

    if (file == NULL) {
        FreeAndNull(indexes);
        PrintFileError();
        exit(1);
    }

    // writing documents
    fwrite(indexes->documentsSize, sizeof(int), 1, file);
    fwrite(indexes->documentsAlloc, sizeof(int), 1, file);

    for (int i = 0; i < *indexes->documentsSize; i++) {
        WriteForwardIndexInBinaryFile(indexes->documents[i], file);
    }

    // writing words
    fwrite(indexes->wordsSize, sizeof(int), 1, file);
    fwrite(indexes->wordsAlloc, sizeof(int), 1, file);

    for (int i = 0; i < *indexes->wordsSize; i++) {
        WriteInvertedIndexInBinaryFile(indexes->words[i], file);
    }

    GreenText();
    printf("The binary file '%s' for the main program has been created in the folder 'binary' successfully.\n", fileName);
    DefaultText();

    fclose(file);
}

Indexes* ReadIndexesFromBinaryFile(Indexes* indexes, char* fileName) {
    char* binaryFileName = NULL;
    binaryFileName = malloc(sizeof(char) * (strlen(fileName) + 8));
    strcpy(binaryFileName, "binary/");
    strcat(binaryFileName, fileName);

    FILE* file = fopen(binaryFileName, "rb");
    FreeAndNull(binaryFileName);

    if (file == NULL) {
        FreeAndNull(indexes);
        PrintFileError();
        exit(1);
    }

    // reading documents
    fread(indexes->documentsSize, sizeof(int), 1, file);
    fread(indexes->documentsAlloc, sizeof(int), 1, file);

    int alloc = STARTER_ALLOC;
    for (int i = 0; i < *indexes->documentsSize; i++) {
        if (i == alloc) {
            alloc *= 2;
            indexes->documents = ReallocDocuments(indexes->documents, &alloc);
        }

        ReadForwardIndexFromBinaryFile(indexes->documents[i], file);
    }

    // reading words
    fread(indexes->wordsSize, sizeof(int), 1, file);
    fread(indexes->wordsAlloc, sizeof(int), 1, file);

    alloc = STARTER_ALLOC;
    for (int i = 0; i < *indexes->wordsSize; i++) {
        if (i == alloc) {
            alloc *= 2;
            indexes->words = ReallocWords(indexes->words, &alloc);
        }

        ReadInvertedIndexFromBinaryFile(indexes->words[i], file);
    }

    fclose(file);

    return indexes;
}

void SearchAndSortNews(Indexes* indexes) {
    int* querySize = malloc(sizeof(int));
    char** queryWords = NULL;

    BoldText();
    printf("• Enter the search: ");
    DefaultText();

    do queryWords = GetUserSentenceInput(querySize);
    while (queryWords == NULL);

    bool somethingFound = false;
    qsort(indexes->words, *indexes->wordsSize, sizeof(InvertedIndex*), CompareWords);
    for (int x = 0; x < *querySize; x++) {
        InvertedIndex** wordIndex = SearchWords(queryWords[x], indexes->words, *indexes->wordsSize);
        if (wordIndex != NULL) {
            somethingFound = true;
            int infoSize = GetWordInfoSize(wordIndex[0]);
            for (int y = 0; y < infoSize; y++) {
                int documentIndex = GetDocumentIndexFromWord(wordIndex[0], y);
                AddTFIDFToSum(indexes->documents[documentIndex], GetTFIDFFromWord(wordIndex[0], y));
            }
        }
    }

    if (somethingFound) {
        qsort(indexes->documents, *indexes->documentsSize, sizeof(ForwardIndex*), CompareTFIDFs);
        PrintNewsResults(indexes->documents, GetDocumentsWithTFIDFNumber(indexes->documents, *indexes->documentsSize));
        ResetTFIDFSums(indexes->documents, *indexes->documentsSize);
    } else {
        RedText();
        printf("No news was found.\n");
        DefaultText();
    }

    ResetUserSearchInput(queryWords, querySize);
    ResetIndexesArrayOrder(indexes);
    printf("\n");
}

void GenerateWordRelatory(Indexes* indexes) {
    BoldText();
    printf("• Enter the word: ");
    DefaultText();

    char* search = GetUserWordInput();

    qsort(indexes->words, *indexes->wordsSize, sizeof(InvertedIndex*), CompareWords);
    InvertedIndex** word = SearchWords(search, indexes->words, *indexes->wordsSize);

    if (word != NULL) {
        int frequency = GetWordInfoSize(word[0]);

        PrintWordFrequencyInDocuments(search, frequency);
        SortWordFrequencyInDocument(word[0]);

        Classes** classes = AllocClasses();
        for (int x = 0; x < frequency; x++) {
            int documentIndex = GetDocumentIndexFromWord(word[0], x);
            char* documentClass = GetDocumentClass(indexes->documents[documentIndex]);

            if (x < 10) PrintDocumentWordResults(indexes->documents[documentIndex], x + 1);
            ReadClasses(classes, documentClass);
        }
        qsort(classes, MAX_CLASSES_NUMBER, sizeof(Classes*), CompareClasses);
        PrintClasses(classes);
        FreeClasses(classes);
    } else {
        RedText();
        printf("The word '%s' does not appear in any documents.\n\n", search);
        DefaultText();
    }

    ResetIndexesArrayOrder(indexes);
    FreeAndNull(search);
}

void ResetIndexesArrayOrder(Indexes* indexes) {
    qsort(indexes->documents, *indexes->documentsSize, sizeof(ForwardIndex*), CompareDocumentsIndex);
    qsort(indexes->words, *indexes->wordsSize, sizeof(InvertedIndex*), CompareWordsIndex);
}
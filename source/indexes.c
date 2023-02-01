#include "libraries.h"

struct Indexes {
    ForwardIndex** documents;
    int* documentsSize;
    int* documentsAlloc;
    InvertedIndex** words;
    int* wordsSize;
    int* wordsAlloc;
};

void GenerateOutputInfo(Indexes* indexes, char* argv) {
    int totalWords = 0;

    for (int x = 0; x < *indexes->wordsSize; x++)
        totalWords += GetWordInfoSize(indexes->words[x]);

    CLEAR_TERMINAL;
    printf(GREEN "The binary file for the main program has been successfully created with the name '%s' in the 'binary' folder. It has %d documents and %d different words.\n\n" DEFAULT, argv, *indexes->documentsSize, totalWords);
}

Indexes* AllocateIndexes() {
    Indexes* indexes = malloc(sizeof(Indexes));

    indexes->documentsSize = calloc(1, sizeof(int));
    indexes->documentsAlloc = malloc(sizeof(int));
    *indexes->documentsAlloc = STARTER_ALLOC;

    indexes->wordsSize = calloc(1, sizeof(int));
    indexes->wordsAlloc = malloc(sizeof(int));
    *indexes->wordsAlloc = STARTER_ALLOC;

    indexes->documents = malloc(STARTER_ALLOC * sizeof(ForwardIndex*));
    indexes->words = malloc(STARTER_ALLOC * sizeof(InvertedIndex*));

    for (int x = 0; x < STARTER_ALLOC; x++) {
        indexes->documents[x] = AllocDocument();
        indexes->words[x] = AllocWord();
    }

    return indexes;
}

Indexes* ReadTrainFile(Indexes* indexes, char* argv) {
    FILE* train = fopen(argv, "r");

    if (!train) {
        FreeAndNull(indexes);
        PrintFileError();
        exit(1);
    }

    printf(GREEN "Reading files, please wait.\n" DEFAULT);
    indexes->documents = ReadDocuments(indexes->documents, train, indexes->documentsSize, indexes->documentsAlloc);
    fclose(train);

    return indexes;
}

void FreeIndexes(Indexes* indexes) {
    for (int x = 0; x < *indexes->documentsAlloc; x++)
        FreeDocument(indexes->documents[x]);

    for (int x = 0; x < *indexes->wordsAlloc; x++)
        FreeWord(indexes->words[x]);

    FreeAndNull(indexes->documents);
    FreeAndNull(indexes->words);
    FreeAndNull(indexes->documentsAlloc);
    FreeAndNull(indexes->wordsAlloc);
    FreeAndNull(indexes->documentsSize);
    FreeAndNull(indexes->wordsSize);
    FreeAndNull(indexes);
}

Indexes* ReadInfo(Indexes* indexes, char* argv) {
    char* argvCopy = IsItTrainOrTestFile(argv);

    for (int i = 0; i < *indexes->documentsSize; i++) {
        char* fileName = GetFileName(indexes->documents[i]);
        size_t pathSize = strlen(argvCopy) + strlen(fileName) + 1;
        char* path = malloc(sizeof(char) * pathSize);

        sprintf(path, "%s%s", argvCopy, fileName);

        FILE* file = fopen(path, "r");
        FreeAndNull(path);

        if (file != NULL) {
            indexes = CreateIndexesFromFile(indexes, file, i);
            fclose(file);
        }
    }

    FreeAndNull(argvCopy);
    indexes = StoreTFIDFFromIndexes(indexes);

    return indexes;
}

Indexes* CreateIndexesFromFile(Indexes* indexes, FILE* file, int documentIndex) {
    char* word = malloc(BUFFER_SIZE * sizeof(char));
    int wordIndex = 0;

    if (file == NULL)
        return NULL;

    while (!feof(file)) {
        if (*indexes->wordsSize == *indexes->wordsAlloc) {
            *indexes->wordsAlloc *= 2;
            indexes->words = ReallocWords(indexes->words, indexes->wordsAlloc);
        }

        word[0] = '\0';

        fscanf(file, "%s", word);

        if (EndOfFile(word[0]))
            continue;

        wordIndex = GetWordIndex(indexes->words, word, *indexes->wordsSize);  // returns -1 if word does not exist
        if (wordIndex != -1) {
            if (WordInDocument(indexes->words[wordIndex], documentIndex))
                indexes->documents[documentIndex] = AddWordFrequencyToForwardIndex(indexes->documents[documentIndex], wordIndex);
            else
                indexes->documents[documentIndex] = StoreWordInfoForwardIndex(indexes->documents[documentIndex], wordIndex);

            indexes->words = AddDocumentFrequencyToInvertedIndex(indexes->words, wordIndex, documentIndex);
            continue;
        }
        // allocates space for the word info array (only for new words)
        indexes->words = AllocWordInfoArray(indexes->words, *indexes->wordsSize);
        indexes->words = StoreWordInvertedIndex(indexes->words, word, *indexes->wordsSize, documentIndex);
        // *indexes->wordsSize works as the current index of the word
        indexes->documents[documentIndex] = StoreWordInfoForwardIndex(indexes->documents[documentIndex], *indexes->wordsSize);
        (*indexes->wordsSize)++;
    }

    FreeAndNull(word);
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

void WriteIndexesInBinaryFile(Indexes* indexes, char* argv) {
    char* binaryFileName = malloc(sizeof(char) * (strlen(argv) + 8));
    sprintf(binaryFileName, "binary/%s", argv);
    FILE* file = fopen(binaryFileName, "wb");
    FreeAndNull(binaryFileName);

    // FILE* file = fopen(argv, "wb"); // use this line and remove above 4 lines in case of hardcode issues

    if (file == NULL) {
        CLEAR_TERMINAL;
        FreeAndNull(indexes);
        printf(BOLD RED "ERROR: Please make sure the 'binary' folder exists in the root of the program. To be sure, use 'make' command and run the program again.\n\n" DEFAULT);
        exit(1);
    }
    // writing documents
    fwrite(indexes->documentsSize, sizeof(int), 1, file);
    fwrite(indexes->documentsAlloc, sizeof(int), 1, file);

    for (int i = 0; i < *indexes->documentsSize; i++)
        WriteForwardIndexInBinaryFile(indexes->documents[i], file);

    // writing words
    fwrite(indexes->wordsSize, sizeof(int), 1, file);
    fwrite(indexes->wordsAlloc, sizeof(int), 1, file);

    for (int i = 0; i < *indexes->wordsSize; i++)
        WriteInvertedIndexInBinaryFile(indexes->words[i], file);

    fclose(file);
}

Indexes* ReadIndexesFromBinaryFile(Indexes* indexes, char* argv) {
    char* binaryFileName = malloc(sizeof(char) * (strlen(argv) + 8));
    sprintf(binaryFileName, "binary/%s", argv);
    FILE* file = fopen(binaryFileName, "rb");
    FreeAndNull(binaryFileName);

    // FILE* file = fopen(argv, "rb"); // use this line and remove above 4 lines in case of hardcode issues

    if (file == NULL) {
        CLEAR_TERMINAL;
        FreeAndNull(indexes);
        printf(BOLD RED "Please make sure the '%s' file exists in the 'binary' folder. To be sure, use 'make' command and run the first program again.\n\n" DEFAULT, argv);
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

    printf(BOLD "• Enter the search: " DEFAULT);
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
        printf(BOLD RED "No results were found.\n" DEFAULT);
    }

    ResetUserSearchInput(queryWords, querySize);
    ResetIndexesArrayOrder(indexes);
    printf("\n");
}

void GenerateWordRelatory(Indexes* indexes) {
    printf(BOLD "• Enter the word: " DEFAULT);
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

            if (x < MAX_RESULTS_NUMBER)
                PrintDocumentWordResults(indexes->documents[documentIndex], x + 1);

            ReadClasses(classes, documentClass);
        }
        qsort(classes, MAX_CLASSES_NUMBER, sizeof(Classes*), CompareClasses);
        PrintClasses(classes);
        FreeClasses(classes);
        ResetIndexesArrayOrder(indexes);
    } else {
        printf(BOLD RED "No results were found in the documents.\n\n" DEFAULT);
    }

    FreeAndNull(search);
}

void ResetIndexesArrayOrder(Indexes* indexes) {
    qsort(indexes->documents, *indexes->documentsSize, sizeof(ForwardIndex*), CompareDocumentsIndex);
    qsort(indexes->words, *indexes->wordsSize, sizeof(InvertedIndex*), CompareWordsIndex);
}

void GenerateDocumentRelatory(Indexes* indexes) {
    AddTotalWordsNumber(indexes->documents, *indexes->documentsSize);
    PrintLongerDocuments(indexes->documents, *indexes->documentsSize);
    PrintShorterDocuments(indexes->documents, *indexes->documentsSize);
    ResetTotalWordsNumber(indexes->documents, *indexes->documentsSize);
    ResetIndexesArrayOrder(indexes);
}

void SortNews(Indexes* indexes, int newsQuantity) {
    int* querySize = malloc(sizeof(int));
    char** queryWords = NULL;

    printf(BOLD "• Enter the search: " DEFAULT);
    do queryWords = GetUserSentenceInput(querySize);
    while (queryWords == NULL);

    int textAlloc = *querySize;
    int textSize = 0;
    TextInfo** text = NULL;
    text = AllocateTextInfoArray(text, textAlloc);

    int wordIndex = 0;

    for (int i = 0; i < textAlloc; i++) {
        wordIndex = GetWordIndexInText(text, textSize, queryWords[i]);
        if (wordIndex != -1)
            text[wordIndex] = AddFrequencyTextInfo(text[wordIndex]);
        else {
            text[textSize] = StoreTextInfo(text[textSize], queryWords[i]);
            textSize++;
        }
    }

    ResetUserSearchInput(queryWords, querySize);

    int wordAppearence = 0;
    char* input;
    bool wordFound = false;

    qsort(indexes->words, *indexes->wordsSize, sizeof(InvertedIndex*), CompareWords);
    for (int i = 0; i < textSize; i++) {
        input = GetWordFromText(text[i]);
        InvertedIndex** word = SearchWords(input, indexes->words, *indexes->wordsSize);
        if (word != NULL) {
            if (!wordFound)
                wordFound = true;

            wordAppearence = GetWordInfoSize(word[0]);
            text[i] = StoreTFIDFTextInfo(text[i], *indexes->documentsSize, wordAppearence);
        }
    }

    ResetIndexesArrayOrder(indexes);

    if (!wordFound) {
        printf(BOLD RED "No results were found in the documents.\n\n" DEFAULT);
    } else {
        float cosine = 0;

        for (int i = 0; i < *indexes->documentsSize; i++) {
            float tfidfProductSum = 0;
            float tfidfSum1 = 0;
            float tfidfSum2 = 0;
            // getting the tfidf from words from the text
            for (int j = 0; j < textSize; j++) {
                input = GetWordFromText(text[j]);
                wordIndex = GetWordIndex(indexes->words, input, *indexes->wordsSize);
                if (wordIndex != -1) {
                    float tfidf1 = GetTFIDFInDocument(indexes->words[wordIndex], i);
                    float tfidf2 = GetTFIDFTextInfo(text[j]);
                    tfidfProductSum += tfidf1 * tfidf2;
                    tfidfSum1 += pow(tfidf1, 2);
                    tfidfSum2 += pow(tfidf2, 2);
                }
            }
            // getting the tfidf from words that are in the document but not in the text
            for (int k = 0; k < GetInfoSizeDocument(indexes->documents[i]); k++) {
                wordIndex = GetWordIndexFromDocument(indexes->documents[i], k);
                input = GetWordByInvertedIndex(indexes->words[wordIndex]);
                if (GetWordIndexInText(text, textSize, input) == -1) {  // checks if input is not in the text
                    float tfidf1 = GetTFIDFInDocument(indexes->words[wordIndex], i);
                    tfidfSum1 += pow(tfidf1, 2);
                }
            }
            if (tfidfProductSum == 0) {
                cosine = 0;
                indexes->documents[i] = StoreCosine(indexes->documents[i], cosine);
                continue;
            }
            cosine = tfidfProductSum / (sqrt(tfidfSum1) * sqrt(tfidfSum2));
            indexes->documents[i] = StoreCosine(indexes->documents[i], cosine);
        }

        qsort(indexes->documents, *indexes->documentsSize, sizeof(ForwardIndex*), CompareCosines);

        for (int i = 0; i < newsQuantity; i++) {
            if (GetDocumentCosine(indexes->documents[i]) == 0)
                newsQuantity = i;  // update newsQuantity in a way that it ignores the cosines = 0
        }

        char* mostFrequentClass = FindMostFrequentDocumentClass(indexes, newsQuantity);

        printf(GREEN "The most likely class of this document is '%s'.\n\n" DEFAULT, mostFrequentClass);
    }

    ResetIndexesArrayOrder(indexes);

    for (int i = 0; i < textAlloc; i++)
        FreeTextInfo(text[i]);

    FreeAndNull(text);
}

char* FindMostFrequentDocumentClass(Indexes* indexes, int size) {
    int maxCount = 1, count = 1;
    float multiplier = 0, maxMultiplier = 0; // variables to be used in case of at least two document with equal maxCounts (tie-breaker)
    char* res = GetDocumentClass(indexes->documents[0]);

    qsort(indexes->documents, size, sizeof(ForwardIndex*), CompareDocumentClasses);  // sort the array by class

    for (int i = 1; i < size; i++) {
        if (strcmp(GetDocumentClass(indexes->documents[i]), GetDocumentClass(indexes->documents[i - 1])) == 0) {
            count++;

            if (count == 2)
                multiplier += GetDocumentCosine(indexes->documents[i - 1]);

            multiplier += GetDocumentCosine(indexes->documents[i]);
        } else {
            if (count > maxCount) {
                maxCount = count;
                maxMultiplier = multiplier;
                res = GetDocumentClass(indexes->documents[i - 1]);
            } else if (count == maxCount) {
                if (multiplier > maxMultiplier) {
                    maxMultiplier = multiplier;
                    res = GetDocumentClass(indexes->documents[i - 1]);
                }
            }

            multiplier = 0;
            count = 1;
        }
    }

    if (count > maxCount) {
        maxCount = count;
        res = GetDocumentClass(indexes->documents[size - 1]);
    }

    return res;
}
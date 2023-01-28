#include "libraries.h"

struct InvertedIndex {
    int index;
    char* word;
    WordInfo** info;
    int infoSize;
    int infoAlloc;
};

void SortWordFrequencyInDocument(InvertedIndex* word) {
    SortWordFrequencyInDocumentByInfo(word->info, word->infoSize);
}

InvertedIndex* AllocWord() {
    return calloc(sizeof(InvertedIndex), 1);
}

InvertedIndex** AllocWordInfoArray(InvertedIndex** words, int wordsSize) {
    words[wordsSize]->infoSize = 0;
    words[wordsSize]->infoAlloc = STARTER_ALLOC;
    words[wordsSize]->info = malloc(STARTER_ALLOC * sizeof(WordInfo*));

    for (int i = 0; i < STARTER_ALLOC; i++) {
        words[wordsSize]->info[i] = AllocWordInfo();
    }

    return words;
}

void FreeWord(InvertedIndex* word) {
    for (int i = 0; i < word->infoAlloc; i++) {
        FreeWordInfo(word->info[i]);
    }

    FreeAndNull(word->info);
    FreeAndNull(word->word);
    FreeAndNull(word);
}

InvertedIndex** ReallocWords(InvertedIndex** words, int* wordsAlloc) {
    InvertedIndex** new = NULL;
    new = realloc(words, *wordsAlloc * sizeof(InvertedIndex*));
    words = new;

    for (int x = *wordsAlloc / 2; x < *wordsAlloc; x++) {
        words[x] = AllocWord();
    }

    return words;
}

InvertedIndex** StoreWordInvertedIndex(InvertedIndex** words, char* word, int wordIndex, int documentIndex) {
    words[wordIndex]->word = strdup(word);
    words[wordIndex]->info = AddWordInfo(words[wordIndex]->info, words[wordIndex]->infoSize, documentIndex);
    words[wordIndex]->index = wordIndex;

    words[wordIndex]->infoSize++;

    return words;
}

int GetWordIndex(InvertedIndex** words, char* word, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(words[i]->word, word) == 0)
            return i;
    }

    return -1;
}

InvertedIndex** AddDocumentFrequencyToInvertedIndex(InvertedIndex** words, int wordIndex, int documentIndex) {
    if (words[wordIndex]->infoSize == words[wordIndex]->infoAlloc) {
        words[wordIndex]->infoAlloc *= 2;
        words[wordIndex]->info = ReallocWordInfoArray(words[wordIndex]->info, words[wordIndex]->infoSize, words[wordIndex]->infoAlloc);
    }

    for (int i = 0; i < words[wordIndex]->infoSize; i++) {
        if (GetDocumentIndexInfo(words[wordIndex]->info[i]) == documentIndex) {
            words[wordIndex]->info[i] = AddDocumentFrequency(words[wordIndex]->info[i]);
            return words;
        }
    }

    words[wordIndex]->info = AddWordInfo(words[wordIndex]->info, words[wordIndex]->infoSize, documentIndex);
    words[wordIndex]->index = wordIndex;
    words[wordIndex]->infoSize++;

    return words;
}

InvertedIndex* StoreTFIDFFromWord(InvertedIndex* word, int documentQuantity) {
    for (int i = 0; i < word->infoSize; i++) {
        word->info[i] = StoreTFIDFFromInfo(word->info[i], documentQuantity, word->infoSize);  // infoSize = somatorio dos frequency;
    }

    return word;
}

bool WordInDocument(InvertedIndex* word, int documentIndex) {
    for (int i = 0; i < word->infoSize; i++) {
        if (GetDocumentIndexInfo(word->info[i]) == documentIndex)
            return true;
    }

    return false;
}

int GetDocumentIndexFromWord(InvertedIndex* word, int j) {
    return GetDocumentIndexInfo(word->info[j]);
}

float GetTFIDFFromWord(InvertedIndex* word, int j) {
    return GetTFIDFInfo(word->info[j]);
}

int GetWordInfoSize(InvertedIndex* word) {
    return word->infoSize;
}

void WriteInvertedIndexInBinaryFile(InvertedIndex* word, FILE* file) {
    if (file == NULL) {
        return;
    }

    fwrite(&word->index, sizeof(int), 1, file);
    int wordSize = strlen(word->word) + 1;
    fwrite(&wordSize, sizeof(int), 1, file);
    fwrite(word->word, sizeof(char), wordSize, file);
    fwrite(&word->infoSize, sizeof(int), 1, file);
    fwrite(&word->infoAlloc, sizeof(int), 1, file);

    for (int i = 0; i < word->infoSize; i++) {
        WriteWordInfoInBinaryFile(word->info[i], file);
    }
}

InvertedIndex* ReadInvertedIndexFromBinaryFile(InvertedIndex* word, FILE* file) {
    if (file == NULL) {
        return NULL;
    }

    fread(&word->index, sizeof(int), 1, file);
    int wordSize = 0;
    fread(&wordSize, sizeof(int), 1, file);
    word->word = malloc(wordSize * sizeof(char));
    fread(word->word, sizeof(char), wordSize, file);
    fread(&word->infoSize, sizeof(int), 1, file);
    fread(&word->infoAlloc, sizeof(int), 1, file);

    word->info = malloc(word->infoAlloc * sizeof(WordInfo*));

    for (int i = 0; i < word->infoAlloc; i++) {
        word->info[i] = AllocWordInfo();
    }

    for (int i = 0; i < word->infoSize; i++) {
        ReadWordInfoFromBinaryFile(word->info[i], file);
    }

    return word;
}

InvertedIndex** SearchWords(char* input, InvertedIndex** words, int wordsSize) {
    InvertedIndex* search = malloc(sizeof(InvertedIndex));
    search->word = strdup(input);

    InvertedIndex** result = bsearch(&search, words, wordsSize, sizeof(InvertedIndex*), CompareWords);

    FreeAndNull(search->word);
    FreeAndNull(search);

    return result;
}

int CompareWords(const void* a, const void* b) {
    return strcmp((*(const InvertedIndex**)a)->word, (*(const InvertedIndex**)b)->word);
}

void PrintWordFrequencyInDocuments(char* search, int frequency) {
    GreenText();
    if (frequency == 1) {
        printf("The word '%s' appears in %d document.\n\n", search, frequency);
    } else {
        printf("The word '%s' appears in %d documents.\n\n", search, frequency);
    }
    DefaultText();
}

int CompareWordsIndex(const void* a, const void* b) {
    return (*(InvertedIndex**)a)->index - (*(InvertedIndex**)b)->index;
}

float GetTFIDFInDocument(InvertedIndex* word, int documentIndex) {
    float tfidf = 0;
    
    for(int i = 0; i < word->infoAlloc; i++) {
        if(word->info[i] != NULL) {
            if(GetDocumentIndexInfo(word->info[i]) == documentIndex) {
                tfidf = GetTFIDFInfo(word->info[i]);
                break;
            }
        }
    }
    
    return tfidf;
}

char* GetWordByInvertedIndex(InvertedIndex* word) {
    return word->word;
}
#include "libraries.h"

struct WordInfo {
    int documentIndex;
    int documentFrequency;
    float tfidf;
};

void SortWordFrequencyInDocumentByInfo(WordInfo** info, int infoSize) {
    qsort(info, infoSize, sizeof(WordInfo*), CompareWordFrequency);
}

int CompareWordFrequency(const void* a, const void* b) {
    return (*(const WordInfo**)b)->documentFrequency - (*(const WordInfo**)a)->documentFrequency;
}

WordInfo* AllocWordInfo() {
    WordInfo* info = malloc(sizeof(WordInfo));

    info->documentIndex = -1;
    info->documentFrequency = 0;
    info->tfidf = -1;

    return info;
}

WordInfo** ReallocWordInfoArray(WordInfo** infoArray, int currentSize, int maximumSize) {
    WordInfo** new;
    new = realloc(infoArray, maximumSize * sizeof(WordInfo*));
    infoArray = new;

    for (int i = currentSize; i < maximumSize; i++) {
        infoArray[i] = AllocWordInfo();
    }

    return infoArray;
}

void FreeWordInfo(WordInfo* info) {
    FreeAndNull(info);
}

WordInfo** AddWordInfo(WordInfo** infoArray, int infoSize, int documentIndex) {
    infoArray[infoSize]->documentIndex = documentIndex;
    infoArray[infoSize]->documentFrequency++;

    return infoArray;
}

WordInfo* AddDocumentFrequency(WordInfo* info) {
    info->documentFrequency++;

    return info;
}

int GetDocumentIndexInfo(WordInfo* info) {
    return info->documentIndex;
}

float GetTFIDFInfo(WordInfo* info) {
    return info->tfidf;
}

WordInfo* StoreTFIDFFromInfo(WordInfo* info, int documentQuantity, int wordAppearance) {  // wordAppearance = how many documents the word showed up
    info->tfidf = CalculateTFIDF(info->documentFrequency, documentQuantity, wordAppearance);

    return info;
}

void WriteWordInfoInBinaryFile(WordInfo* info, FILE* file) {
    if (file == NULL) {
        return;
    }

    fwrite(&info->documentIndex, sizeof(int), 1, file);
    fwrite(&info->documentFrequency, sizeof(int), 1, file);
    fwrite(&info->tfidf, sizeof(float), 1, file);
}

void ReadWordInfoFromBinaryFile(WordInfo* info, FILE* file) {
    if (file == NULL) {
        return;
    }

    fread(&info->documentIndex, sizeof(int), 1, file);
    fread(&info->documentFrequency, sizeof(int), 1, file);
    fread(&info->tfidf, sizeof(float), 1, file);
}
#include "libraries.h"

struct WordInfo {
    int documentIndex;
    int documentFrequency;
    float TFIDF;
};

WordInfo* AllocWordInfo() {
    WordInfo* info = NULL;

    info = malloc(sizeof(WordInfo));
    info->documentIndex = -1;
    info->documentFrequency = 0;
    info->TFIDF = -1;

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
    return info->TFIDF;
}

WordInfo* StoreTFIDFFromInfo(WordInfo* info, int documentQuantity, int wordAppearance) {  // wordAppearance = how many documents the word showed up
    info->TFIDF = CalculateTFIDF(info->documentFrequency, documentQuantity, wordAppearance);

    return info;
}

void WriteWordInfoInBinaryFile(WordInfo* info, FILE* file) {
    if (file == NULL) {
        return;
    }

    fwrite(&info->documentIndex, sizeof(int), 1, file);
    fwrite(&info->documentFrequency, sizeof(int), 1, file);
    fwrite(&info->TFIDF, sizeof(float), 1, file);
}

void ReadWordInfoFromBinaryFile(WordInfo* info, FILE* file) {
    if (file == NULL) {
        return;
    }

    fread(&info->documentIndex, sizeof(int), 1, file);
    fread(&info->documentFrequency, sizeof(int), 1, file);
    fread(&info->TFIDF, sizeof(float), 1, file);
}
#include "libraries.h"

struct DocumentInfo {
    int wordIndex;
    int wordFrequency;
    float tfidf;
};

int GetDocumentWordFrequency(DocumentInfo* info) {
    return info->wordFrequency;
}

DocumentInfo* AllocDocumentInfo() {
    DocumentInfo* info = malloc(sizeof(DocumentInfo));
    
    info->wordIndex = -1;
    info->wordFrequency = 0;
    info->tfidf = -1;

    return info;
}

void FreeDocumentInfo(DocumentInfo* info) {
    FreeAndNull(info);
}

DocumentInfo** ReallocDocumentInfoArray(DocumentInfo** infoArray, int currentSize, int maximumSize) {
    DocumentInfo** new;
    new = realloc(infoArray, maximumSize * sizeof(DocumentInfo*));
    infoArray = new;

    for (int i = currentSize; i < maximumSize; i++) {
        infoArray[i] = AllocDocumentInfo();
    }

    return infoArray;
}

DocumentInfo** AddDocumentInfo(DocumentInfo** infoArray, int infoSize, int wordIndex) {
    infoArray[infoSize]->wordIndex = wordIndex;
    infoArray[infoSize]->wordFrequency++;

    return infoArray;
}

int GetWordIndexInfo(DocumentInfo* info) {
    return info->wordIndex;
}

DocumentInfo* AddWordFrequency(DocumentInfo* info) {
    info->wordFrequency++;

    return info;
}

DocumentInfo* StoreTFIDFFromDocumentInfo(DocumentInfo* info, int documentQuantity, int wordAppearance) {
    info->tfidf = CalculateTFIDF(info->wordFrequency, documentQuantity, wordAppearance);

    return info;
}

void WriteDocumentInfoInBinaryFile(DocumentInfo* info, FILE* file) {
    if (file == NULL) {
        return;
    }

    fwrite(&info->wordIndex, sizeof(int), 1, file);
    fwrite(&info->wordFrequency, sizeof(int), 1, file);
    fwrite(&info->tfidf, sizeof(float), 1, file);
}

void ReadDocumentInfoFromBinaryFile(DocumentInfo* info, FILE* file) {
    if (file == NULL) {
        return;
    }

    fread(&info->wordIndex, sizeof(int), 1, file);
    fread(&info->wordFrequency, sizeof(int), 1, file);
    fread(&info->tfidf, sizeof(float), 1, file);
}
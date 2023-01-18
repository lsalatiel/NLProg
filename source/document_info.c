#include "libraries.h"

struct DocumentInfo {
    int word_index;
    int word_frequency;
    float tf_idf;
};

DocumentInfo* AllocDocumentInfo() {
    DocumentInfo* info = NULL;
    info = malloc(sizeof(DocumentInfo));
    info->word_index = -1;
    info->word_frequency = 0;
    info->tf_idf = -1;

    return info;
}

void FreeDocumentInfo(DocumentInfo* info) {
    FreeAndNull(info);
}

DocumentInfo** ReallocDocumentInfoArray(DocumentInfo** info_array, int curr_size, int max_size) {
    DocumentInfo** new;
    new = realloc(info_array, max_size * sizeof(DocumentInfo*));
    info_array = new;

    for (int i = curr_size; i < max_size; i++) {
        info_array[i] = AllocDocumentInfo();
    }

    return info_array;
}

DocumentInfo** AddDocumentInfo(DocumentInfo** info_array, int info_size, int word_index) {
    info_array[info_size]->word_index = word_index;
    info_array[info_size]->word_frequency++;

    return info_array;
}

int GetWordIndexInfo(DocumentInfo* info) {
    return info->word_index;
}

DocumentInfo* AddWordFrequency(DocumentInfo* info) {
    info->word_frequency++;

    return info;
}

DocumentInfo* StoreTFIDFFromDocumentInfo(DocumentInfo* info, int document_quantity, int word_appearance) {
    info->tf_idf = CalculateTf_idf(info->word_frequency, document_quantity, word_appearance);

    return info;
}

void WriteDocumentInfoInBinaryFile(DocumentInfo* info, FILE* file) {
    if (file == NULL) {
        return;
    }

    fwrite(&info->word_index, sizeof(int), 1, file);
    fwrite(&info->word_frequency, sizeof(int), 1, file);
    fwrite(&info->tf_idf, sizeof(float), 1, file);
}

void ReadDocumentInfoFromBinaryFile(DocumentInfo* info, FILE* file) {
    if (file == NULL) {
        return;
    }

    fread(&info->word_index, sizeof(int), 1, file);
    fread(&info->word_frequency, sizeof(int), 1, file);
    fread(&info->tf_idf, sizeof(float), 1, file);
}
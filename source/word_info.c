#include "libraries.h"

struct WordInfo {
    int document_index;
    int document_frequency;
    float tf_idf;
};

WordInfo* AllocateWordInfo() {
    WordInfo* info = NULL;

    info = malloc(sizeof(WordInfo));
    info->document_index = -1;
    info->document_frequency = 0;
    info->tf_idf = -1;

    return info;
}

WordInfo** ReallocWordInfoArray(WordInfo** info_array, int curr_size, int max_size) {
    WordInfo** new;
    new = realloc(info_array, max_size * sizeof(WordInfo*));
    info_array = new;

    for (int i = curr_size; i < max_size; i++) {
        info_array[i] = AllocateWordInfo();
    }

    return info_array;
}

void FreeWordInfo(WordInfo* info) {
    FreeAndNull(info);
}

WordInfo** AddWordInfo(WordInfo** info_array, int info_size, int document_index) {
    info_array[info_size]->document_index = document_index;
    info_array[info_size]->document_frequency++;

    return info_array;
}

WordInfo* AddDocumentFrequency(WordInfo* info) {
    info->document_frequency++;

    return info;
}

int GetDocumentIndexInfo(WordInfo* info) {
    return info->document_index;
}

WordInfo* StoreTf_idfFromInfo(WordInfo* info, int document_quantity, int word_appearance) {  // word_appearance = how many documents the word showed up
    info->tf_idf = CalculateTf_idf(info->document_frequency, document_quantity, word_appearance);

    return info;
}

// float CalculateTf_idf(int frequency, int document_quantity, int word_appearance) {
//     float tf = frequency;

//     float x = (1 + document_quantity) / (1 + word_appearance);
//     float idf = log(x) + 1;

//     float tf_idf = tf * idf;

//     return tf_idf;
// }

void WriteWordInfoInBinaryFile(WordInfo* info, FILE* file) {
    if (file == NULL) {
        return;
    }

    fwrite(&info->document_index, sizeof(int), 1, file);
    fwrite(&info->document_frequency, sizeof(int), 1, file);
    fwrite(&info->tf_idf, sizeof(float), 1, file);
}

void ReadWordInfoFromBinaryFile(WordInfo* info, FILE* file) {
    if (file == NULL) {
        return;
    }

    fread(&info->document_index, sizeof(int), 1, file);
    fread(&info->document_frequency, sizeof(int), 1, file);
    fread(&info->tf_idf, sizeof(float), 1, file);
}
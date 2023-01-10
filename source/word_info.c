#include "libraries.h"

struct WordInfo {
    int document_index;
    int document_frequency;
    int tf_idf;
};

WordInfo* AllocateWordInfo(WordInfo* info) {
    info = calloc(sizeof(WordInfo), 1);

    info->document_index = -1;
    info->document_frequency = 0;
    info->tf_idf = -1;

    return info;
}

// WordInfo* ReallocWordInfo(WordInfo* info, int size) {
//     info = realloc(info, size);

//     return info;
// }

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
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

WordInfo* AddDocumentFrequency(WordInfo** info, int document_index) {
    

    return info;
}
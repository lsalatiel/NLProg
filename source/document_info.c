#include "libraries.h"

struct DocumentInfo {
    int word_index;
    int word_frequency;
    float tf_idf;
};

DocumentInfo* AllocateDocumentInfo(DocumentInfo* info) {
    info = calloc(sizeof(DocumentInfo), 1);

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
    
    for(int i = curr_size; i < max_size; i++) {
        info_array[i] = AllocateDocumentInfo(info_array[i]);
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

DocumentInfo* StoreTf_idfFromDocumentInfo(DocumentInfo* info, int document_quantity, int word_appearance) {
    info->tf_idf = CalculateTf_idf(info->word_frequency, document_quantity, word_appearance);

    return info;
}
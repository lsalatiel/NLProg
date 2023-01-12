#include "libraries.h"

struct DocumentInfo {
    int word_index;
    int word_frequency;
    float tf_idf;
};

DocumentInfo* AllocateDocumentsInfo() {
    return calloc(sizeof(DocumentInfo), 1);
}

void FreeDocumentsInfo(DocumentInfo* info) {
    FreeAndNull(info);
}

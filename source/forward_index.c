#include "libraries.h"

struct ForwardIndex {
    int index;
    char** name;
    char** class;
    DocumentInfo** info;
    int info_size;
    int info_alloc;
};

ForwardIndex* AllocateDocuments() {
    return calloc(sizeof(ForwardIndex), 1);
}

void FreeDocuments(ForwardIndex* documents) {
    FreeAndNull(documents);
}
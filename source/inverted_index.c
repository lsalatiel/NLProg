#include "libraries.h"

struct InvertedIndex {
    int index;
    char** word;
    WordInfo** info;
    int info_size;
    int info_alloc;
};

InvertedIndex* AllocateWords() {
    return calloc(sizeof(InvertedIndex), 1);
}

void FreeWords(InvertedIndex* words) {
    FreeAndNull(words);
}
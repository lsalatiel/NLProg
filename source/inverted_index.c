#include "libraries.h"

struct InvertedIndex {
    int index;
    char* word;
    WordInfo** info;
    int info_size;
    int info_alloc;
};

InvertedIndex* AllocateWords() {
    InvertedIndex* word = calloc(sizeof(InvertedIndex), 1);

    return word;
}

InvertedIndex* AllocateWordInfoArray(InvertedIndex* word, int size) {
    // word->info_size = 0;
    // word->info_alloc = size;
    
    word->info = malloc(size * sizeof(WordInfo*));

    for (int i = 0; i < size; i++) {
        word->info[i] = AllocateWordInfo(word->info[i]);
    }

    return word;
}

void FreeWords(InvertedIndex* words) {
    FreeAndNull(words);
}

InvertedIndex** ReallocWords(InvertedIndex** words, int* words_alloc) {
    InvertedIndex** new = NULL;
    new = realloc(words, *words_alloc * sizeof(InvertedIndex*));
    words = new;

    for (int x = *words_alloc / 2; x < *words_alloc; x++) {
        words[x] = AllocateWords();
    }

    return words;
}


InvertedIndex** StoreWordInvertedIndex(InvertedIndex** words, char* word, int index) {
    if(words[index]->info_size == words[index]->info_alloc) {
        words[index]->info_alloc *= 2;
        words[index]->info = ReallocWordInfo(words[index]->info, words[index]->info_alloc);
    }
    
    words[index] = strdup(word);
    words[index]->info_size++;



    return words;
}

// bool IsRepeatedWord(InvertedIndex** words, char* word, int size) {
//     char* search = (char*)bsearch(word, words, size, sizeof(char), CompareStringToInvertedIndex);

//     if(search == NULL) {
//         return false;
//     }
//     return true;
// }

// int CompareStringToInvertedIndex(const void* a, const void* b) {
//     InvertedIndex* b1 = (InvertedIndex*)b;

//     return strcmp((char*)a, b1->word);
// }

int GetWordIndex(InvertedIndex** words, char* word, int size) {
    for(int i = 0; i < size; i++) {
        if(strcmp(words[i]->word, word))
            return i;
    }

    return -1;
}

InvertedIndex** AddDocumentFrequencyToInvertedIndex(InvertedIndex** words, int word_index, int document_index) {
    words[word_index]->info = AddDocumentFrequency(words[word_index]->info, document_index);
}
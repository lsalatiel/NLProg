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

InvertedIndex* AllocateWordInfoArray(InvertedIndex** words, int words_size, int max_size) {
    words[words_size]->info_size = 0;
    words[words_size]->info_alloc = max_size;
    
    words[words_size]->info = malloc(max_size * sizeof(WordInfo*));

    for (int i = 0; i < max_size; i++) {
        words[words_size]->info[i] = AllocateWordInfo(words[words_size]->info[i]);
    }

    return words[words_size];
}

void FreeWord(InvertedIndex* word) {
    for(int i = 0; i < word->info_alloc; i++) {
        FreeWordInfo(word->info[i]);
    }

    FreeAndNull(word->info);

    FreeAndNull(word->word);
    FreeAndNull(word);
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


InvertedIndex** StoreWordInvertedIndex(InvertedIndex** words, char* word, int word_index, int document_index) {
    // if(words[word_index]->info_size == words[word_index]->info_alloc) {
    //     words[word_index]->info_alloc *= 2;
    //     words[word_index]->info = ReallocWordInfo(words[word_index]->info, words[word_index]->info_alloc);
    // }
    
    words[word_index]->word = strdup(word);
    words[word_index]->info = AddWordInfo(words[word_index]->info, words[word_index]->info_size, document_index);

    //words[word_index]->info_size++;

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
        if(strcmp(words[i]->word, word) == 0)
            return i;
    }

    return -1;
}

InvertedIndex** AddDocumentFrequencyToInvertedIndex(InvertedIndex** words, int word_index, int document_index) {
    words[word_index]->info[document_index] = AddDocumentFrequency(words[word_index]->info[document_index]);

    return words;
}
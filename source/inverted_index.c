#include "libraries.h"

struct InvertedIndex {
    int index;
    char* word;
    WordInfo** info;
    int info_size;
    int info_alloc;
};

InvertedIndex* AllocateWord() {
    InvertedIndex* word = calloc(sizeof(InvertedIndex), 1);

    return word;
}

InvertedIndex** AllocateWordInfoArray(InvertedIndex** words, int words_size, int max_size) {
    words[words_size]->info_size = 0;
    words[words_size]->info_alloc = STARTER_ALLOC;
    
    words[words_size]->info = malloc(STARTER_ALLOC * sizeof(WordInfo*));

    for (int i = 0; i < STARTER_ALLOC; i++) {
        words[words_size]->info[i] = AllocateWordInfo(words[words_size]->info[i]);
    }

    return words;
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
    words[word_index]->word = strdup(word);
    words[word_index]->info = AddWordInfo(words[word_index]->info, words[word_index]->info_size, document_index);

    words[word_index]->info_size++;

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
    if(words[word_index]->info_size == words[word_index]->info_alloc) {
        words[word_index]->info_alloc *= 2;
        words[word_index]->info = ReallocWordInfoArray(words[word_index]->info, words[word_index]->info_size, words[word_index]->info_alloc);
    }
    
    for(int i = 0; i < words[word_index]->info_size; i++) {
        if(GetDocumentIndexInfo(words[word_index]->info[i]) == document_index) {
            words[word_index]->info[i] = AddDocumentFrequency(words[word_index]->info[i]);
            return words;
        }
    }
    
    words[word_index]->info = AddWordInfo(words[word_index]->info, words[word_index]->info_size, document_index);
    words[word_index]->info_size++;

    return words;
}

InvertedIndex* StoreTf_idfFromfWord(InvertedIndex* word, int document_quantity) {
    for(int i = 0; i < word->info_size; i++) {
        word->info[i] = StoreTf_idfFromInfo(word->info[i], document_quantity, word->info_size); // somatorio dos frequency;
    }

    return word;
}

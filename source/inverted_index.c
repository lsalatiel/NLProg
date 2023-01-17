#include "libraries.h"

struct InvertedIndex {
    int index;
    char* word;
    WordInfo** info;
    int info_size;
    int info_alloc;
};

InvertedIndex* AllocateWord() {
    return calloc(sizeof(InvertedIndex), 1);
}

InvertedIndex** AllocateWordInfoArray(InvertedIndex** words, int words_size) {
    words[words_size]->info_size = 0;
    words[words_size]->info_alloc = STARTER_ALLOC;
    words[words_size]->info = malloc(STARTER_ALLOC * sizeof(WordInfo*));

    for (int i = 0; i < STARTER_ALLOC; i++) {
        words[words_size]->info[i] = AllocateWordInfo();
    }

    return words;
}

void FreeWord(InvertedIndex* word) {
    for (int i = 0; i < word->info_alloc; i++) {
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
        words[x] = AllocateWord();
    }

    return words;
}

InvertedIndex** StoreWordInvertedIndex(InvertedIndex** words, char* word, int word_index, int document_index) {
    words[word_index]->word = strdup(word);
    words[word_index]->info = AddWordInfo(words[word_index]->info, words[word_index]->info_size, document_index);
    words[word_index]->index = word_index;

    words[word_index]->info_size++;

    return words;
}

int GetWordIndex(InvertedIndex** words, char* word, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(words[i]->word, word) == 0)
            return i;
    }

    return -1;
}

InvertedIndex** AddDocumentFrequencyToInvertedIndex(InvertedIndex** words, int word_index, int document_index) {
    if (words[word_index]->info_size == words[word_index]->info_alloc) {
        words[word_index]->info_alloc *= 2;
        words[word_index]->info = ReallocWordInfoArray(words[word_index]->info, words[word_index]->info_size, words[word_index]->info_alloc);
    }

    for (int i = 0; i < words[word_index]->info_size; i++) {
        if (GetDocumentIndexInfo(words[word_index]->info[i]) == document_index) {
            words[word_index]->info[i] = AddDocumentFrequency(words[word_index]->info[i]);
            return words;
        }
    }

    words[word_index]->info = AddWordInfo(words[word_index]->info, words[word_index]->info_size, document_index);
    words[word_index]->index = word_index;
    words[word_index]->info_size++;

    return words;
}

InvertedIndex* StoreTf_idfFromfWord(InvertedIndex* word, int document_quantity) {
    for (int i = 0; i < word->info_size; i++) {
        word->info[i] = StoreTf_idfFromInfo(word->info[i], document_quantity, word->info_size);  // info_size = somatorio dos frequency;
    }

    return word;
}

bool WordInDocument(InvertedIndex* word, int document_index) {
    for (int i = 0; i < word->info_size; i++) {
        if (GetDocumentIndexInfo(word->info[i]) == document_index)
            return true;
    }

    return false;
}

int GetDocumentIndexFromWord(InvertedIndex* word, int j) {
    return GetDocumentIndexInfo(word->info[j]);
}

float GetTFIDFFromWord(InvertedIndex* word, int j) {
    return GetTFIDFInfo(word->info[j]);
}

int GetWordInfoSize(InvertedIndex* word) {
    return word->info_size;
}

void WriteInvertedIndexInBinaryFile(InvertedIndex* word, FILE* file) {
    if (file == NULL) {
        return;
    }

    fwrite(&word->index, sizeof(int), 1, file);
    int word_size = strlen(word->word) + 1;
    fwrite(&word_size, sizeof(int), 1, file);
    fwrite(word->word, sizeof(char), word_size, file);
    fwrite(&word->info_size, sizeof(int), 1, file);
    fwrite(&word->info_alloc, sizeof(int), 1, file);

    for (int i = 0; i < word->info_size; i++) {
        WriteWordInfoInBinaryFile(word->info[i], file);
    }
}

InvertedIndex* ReadInvertedIndexFromBinaryFile(InvertedIndex* word, FILE* file) {
    if (file == NULL) {
        return NULL;
    }

    fread(&word->index, sizeof(int), 1, file);
    int word_size = 0;
    fread(&word_size, sizeof(int), 1, file);
    word->word = malloc(word_size * sizeof(char));
    fread(word->word, sizeof(char), word_size, file);
    fread(&word->info_size, sizeof(int), 1, file);
    fread(&word->info_alloc, sizeof(int), 1, file);

    word->info = malloc(word->info_alloc * sizeof(WordInfo*));

    for (int i = 0; i < word->info_alloc; i++) {
        word->info[i] = AllocateWordInfo();
    }

    for (int i = 0; i < word->info_size; i++) {
        ReadWordInfoFromBinaryFile(word->info[i], file);
    }

    return word;
}

void SortWords(InvertedIndex** words, int words_size) {
    qsort(words, words_size, sizeof(InvertedIndex*), CompareWords);
}

InvertedIndex* SearchWords(char* input, InvertedIndex** words, int words_size) {
    InvertedIndex search_key;
    search_key.word = input;
    InvertedIndex* result = (InvertedIndex*)bsearch(&search_key, words, words_size, sizeof(InvertedIndex), CompareWords2);
    return result;
}

int CompareWords(const void* a, const void* b) {
    InvertedIndex* word_index_a = *(InvertedIndex**)a;
    InvertedIndex* word_index_b = *(InvertedIndex**)b;
    return strcmp(word_index_a->word, word_index_b->word);
}

int CompareWords2(const void* a, const void* b) {
    InvertedIndex* word_index_a = (InvertedIndex*)a;
    InvertedIndex* word_index_b = (InvertedIndex*)b;
    return strcmp(word_index_a->word, word_index_b->word);
}
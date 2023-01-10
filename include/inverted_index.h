#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

typedef struct InvertedIndex InvertedIndex;

InvertedIndex* AllocateWords();

InvertedIndex* AllocateWordInfoArray(InvertedIndex** words, int words_size, int max_size);

InvertedIndex** ReallocWords(InvertedIndex** words, int* words_alloc);

void FreeWord(InvertedIndex* word);

int GetWordIndex(InvertedIndex** words, char* word, int size);

InvertedIndex** StoreWordInvertedIndex(InvertedIndex** words, char* word, int word_index, int document_index);

InvertedIndex** AddDocumentFrequencyToInvertedIndex(InvertedIndex** words, int word_index, int document_index);


#endif
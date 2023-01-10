#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

typedef struct InvertedIndex InvertedIndex;

InvertedIndex* AllocateWords();

InvertedIndex* AllocateWordInfoArray(InvertedIndex* word, int size);

void FreeWords(InvertedIndex* words);

int GetWordIndex(InvertedIndex** words, char* word, int size);

InvertedIndex** StoreWordInvertedIndex(InvertedIndex** words, char* word, int index);

InvertedIndex** AddDocumentFrequencyToInvertedIndex(InvertedIndex** words, int index, int document_index);

#endif
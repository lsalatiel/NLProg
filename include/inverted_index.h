#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

typedef struct InvertedIndex InvertedIndex;

InvertedIndex* AllocateWords();
void FreeWords(InvertedIndex* words);

#endif
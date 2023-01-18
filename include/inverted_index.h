#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

typedef struct InvertedIndex InvertedIndex;

/**
 * @brief allocates space for a single inverted index
 */
InvertedIndex* AllocWord();

/**
 * @brief allocates and initialize the information of a single inverted index
 */
InvertedIndex** AllocWordInfoArray(InvertedIndex** words, int wordsSize);

/**
 * @brief reallocates space for the information of an inverted index array
 */
InvertedIndex** ReallocWords(InvertedIndex** words, int* wordsAlloc);

/**
 * @brief frees memory allocated for a single word
 */
void FreeWord(InvertedIndex* word);

/**
 * @brief returns the index of a word in the array if it exists, otherwise it returns -1
 */
int GetWordIndex(InvertedIndex** words, char* word, int size);

/**
 * @brief stores the word and the information of a single inverted index
 */
InvertedIndex** StoreWordInvertedIndex(InvertedIndex** words, char* word, int wordIndex, int documentIndex);

/**
 * @brief stores information of a word that is already stored
 */
InvertedIndex** AddDocumentFrequencyToInvertedIndex(InvertedIndex** words, int wordIndex, int documentIndex);

/**
 * @brief stores TFIDF of each word of the inverted index
 */
InvertedIndex* StoreTFIDFFromWord(InvertedIndex* word, int documentQuantity);

/**
 * @brief checks if a certain word is in a specific document
 */
bool WordInDocument(InvertedIndex* word, int documentIndex);

/**
 * @brief returns the size of the word info array
 */
int GetWordInfoSize(InvertedIndex* word);

/**
 * @brief writes an inverted index in a binary file
 */
void WriteInvertedIndexInBinaryFile(InvertedIndex* word, FILE* file);

/**
 * @brief reads an inverted index from a binary file
 */
InvertedIndex* ReadInvertedIndexFromBinaryFile(InvertedIndex* word, FILE* file);

/**
 * @brief search an user given word in the InvertedIndex array
 */
InvertedIndex** SearchWords(char* input, InvertedIndex** words, int wordsSize);

/**
 * @brief comparison function for qsort() based on alphabetical order
 */
int CompareWords(const void* a, const void* b);

/**
 * @brief returns the document index that a given word appear on
 */
int GetDocumentIndexFromWord(InvertedIndex* word, int j);

/**
 * @brief returns the tf-idf from a word
 */
float GetTFIDFFromWord(InvertedIndex* word, int j);

void SortWordFrequencyInDocument(InvertedIndex* word);

void PrintWordFrequencyInDocuments(char* search, int frequency);

/**
 * @brief comparison function for qsort() based on ascending words index order
 */
int CompareWordsIndex(const void* a, const void* b);

#endif
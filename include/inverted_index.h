#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

typedef struct InvertedIndex InvertedIndex;

/**
 * @brief allocates space for a single inverted index
 * 
 * @return InvertedIndex* 
 */
InvertedIndex* AllocateWord();

/**
 * @brief allocates and initialize the information of a single inverted index
 * 
 * @param words 
 * @param words_size 
 * @param max_size 
 * @return InvertedIndex** 
 */
InvertedIndex** AllocateWordInfoArray(InvertedIndex** words, int words_size);

/**
 * @brief reallocates space for the information of an inverted index array
 * 
 * @param words 
 * @param words_alloc 
 * @return InvertedIndex** 
 */
InvertedIndex** ReallocWords(InvertedIndex** words, int* words_alloc);

/**
 * @brief frees memory allocated for a single word
 * 
 * @param word 
 */
void FreeWord(InvertedIndex* word);

/**
 * @brief returns the index of a word in the array if it exists, otherwise it returns -1
 * 
 * @param words 
 * @param word 
 * @param size 
 * @return int 
 */
int GetWordIndex(InvertedIndex** words, char* word, int size);

/**
 * @brief stores the word and the information of a single inverted index
 * 
 * @param words 
 * @param word 
 * @param word_index 
 * @param document_index 
 * @return InvertedIndex** 
 */
InvertedIndex** StoreWordInvertedIndex(InvertedIndex** words, char* word, int word_index, int document_index);

/**
 * @brief stores information of a word that is already stored
 * 
 * @param words 
 * @param word_index 
 * @param document_index 
 * @return InvertedIndex** 
 */
InvertedIndex** AddDocumentFrequencyToInvertedIndex(InvertedIndex** words, int word_index, int document_index);

/**
 * @brief stores tf_idf of each word of the inverted index
 * 
 * @param word 
 * @param document_quantity 
 * @return InvertedIndex* 
 */
InvertedIndex* StoreTf_idfFromfWord(InvertedIndex* word, int document_quantity);


bool WordInDocument(InvertedIndex* word, int document_index);

int GetWordInfoSize(InvertedIndex* word);

#endif
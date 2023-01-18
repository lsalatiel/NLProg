#ifndef WORD_INFO_H
#define WORD_INFO_H

typedef struct WordInfo WordInfo;

/**
 * @brief allocates space and initialize a word info structure
 */
WordInfo* AllocWordInfo();

/**
 * @brief reallocates space fora a word info array
 */
WordInfo** ReallocWordInfoArray(WordInfo** infoArray, int currentSize, int maximumSize);

/**
 * @brief frees memory allocatd for a word info
 */
void FreeWordInfo(WordInfo* info);

/**
 * @brief updates the information of a word
 */
WordInfo** AddWordInfo(WordInfo** infoArray, int infoSize, int documentIndex);

/**
 * @brief updates the documentFrequency variable (adds one)
 */
WordInfo* AddDocumentFrequency(WordInfo* info);

/**
 * @brief returns documentIndex of a wordInfo
 */
int GetDocumentIndexInfo(WordInfo* info);

/**
 * @brief stores TFIDF of a word in a specific document to the wordInfo
 */
WordInfo* StoreTFIDFFromInfo(WordInfo* info, int documentQuantity, int wordAppearance);

/**
 * @brief writes a wordInfo structure in a binary file
 */
void WriteWordInfoInBinaryFile(WordInfo* info, FILE* file);

/**
 * @brief reads a wordInfo structure from a binary file
 */
void ReadWordInfoFromBinaryFile(WordInfo* info, FILE* file);

/**
 * @brief returns the tf-idf
 */
float GetTFIDFInfo(WordInfo* info);

/**
 * @brief sorts an word info array based on appearance descending order
 */
void SortWordFrequencyInDocumentByInfo(WordInfo** info, int infoSize);

/**
 * @brief comparison function for qsort() based on descending word appearance order
 */
int CompareWordFrequency(const void* a, const void* b);

#endif
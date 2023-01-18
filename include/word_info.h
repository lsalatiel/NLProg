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
WordInfo** ReallocWordInfoArray(WordInfo** info_array, int curr_size, int max_size);

/**
 * @brief frees memory allocatd for a word info
 */
void FreeWordInfo(WordInfo* info);

/**
 * @brief updates the information of a word
 */
WordInfo** AddWordInfo(WordInfo** info_array, int info_size, int document_index);

/**
 * @brief updates the document_frequency variable (adds one)
 */
WordInfo* AddDocumentFrequency(WordInfo* info);

/**
 * @brief returns document_index of a word_info
 */
int GetDocumentIndexInfo(WordInfo* info);

/**
 * @brief stores tf_idf of a word in a specific document to the word_info
 */
WordInfo* StoreTf_idfFromInfo(WordInfo* info, int document_quantity, int word_appearance);

/**
 * @brief writes a word_info structure in a binary file
 */
void WriteWordInfoInBinaryFile(WordInfo* info, FILE* file);

/**
 * @brief reads a word_info structure from a binary file
 */
void ReadWordInfoFromBinaryFile(WordInfo* info, FILE* file);

/**
 * @brief returns the tf-idf
 */
float GetTFIDFInfo(WordInfo* info);

#endif
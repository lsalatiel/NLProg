#ifndef WORD_INFO_H
#define WORD_INFO_H

typedef struct WordInfo WordInfo;

/**
 * @brief allocates space and initialize a word info structure
 *
 * @param info
 * @return WordInfo*
 */
WordInfo* AllocateWordInfo();

/**
 * @brief reallocates space fora a word info array
 *
 * @param info_array
 * @param curr_size
 * @param max_size
 * @return WordInfo**
 */
WordInfo** ReallocWordInfoArray(WordInfo** info_array, int curr_size, int max_size);

/**
 * @brief frees memory allocatd for a word info
 *
 * @param info
 */
void FreeWordInfo(WordInfo* info);

/**
 * @brief updates the information of a word
 *
 * @param info_array
 * @param info_size
 * @param document_index
 * @return WordInfo**
 */
WordInfo** AddWordInfo(WordInfo** info_array, int info_size, int document_index);

/**
 * @brief updates the document_frequency variable (adds one)
 *
 * @param info
 * @return WordInfo*
 */
WordInfo* AddDocumentFrequency(WordInfo* info);

/**
 * @brief returns document_index of a word_info
 *
 * @param info
 * @return int
 */
int GetDocumentIndexInfo(WordInfo* info);

/**
 * @brief stores tf_idf of a word in a specific document to the word_info
 *
 * @param info
 * @param document_quantity
 * @param word_appearance
 * @return WordInfo*
 */
WordInfo* StoreTf_idfFromInfo(WordInfo* info, int document_quantity, int word_appearance);

/**
 * @brief saves a word_info structure in a binary file
 *
 * @param info
 * @param file
 */
void WriteWordInfoInBinaryFile(WordInfo* info, FILE* file);

void ReadWordInfoFromBinaryFile(WordInfo* info, FILE* file);

float GetTFIDFInfo(WordInfo* info);

#endif
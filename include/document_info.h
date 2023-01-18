#ifndef DOCUMENT_INFO_H
#define DOCUMENT_INFO_H

typedef struct DocumentInfo DocumentInfo;

/**
 * @brief allocates space and initialize a document info structure
 */
DocumentInfo* AllocDocumentInfo();

/**
 * @brief frees memory allocatd for a document info
 */
void FreeDocumentInfo(DocumentInfo* info);

/**
 * @brief reallocates space fora a document info array
 */
DocumentInfo** ReallocDocumentInfoArray(DocumentInfo** info_array, int curr_size, int max_size);

/**
 * @brief updates the information of a document
 */
DocumentInfo** AddDocumentInfo(DocumentInfo** info_array, int info_size, int word_index);

/**
 * @brief returns the word_index of a document_info
 */
int GetWordIndexInfo(DocumentInfo* info);

/**
 * @brief updates the word_frequency variable (adds one)
 */
DocumentInfo* AddWordFrequency(DocumentInfo* info);

/**
 * @brief stores tf_idf of a word in a specific document to the document_info
 */
DocumentInfo* StoreTFIDFFromDocumentInfo(DocumentInfo* info, int document_quantity, int word_appearance);

/**
 * @brief writes a document_info structure in a binary file
 */
void WriteDocumentInfoInBinaryFile(DocumentInfo* info, FILE* file);

/**
 * @brief reads a document info structure from a binary file
 */
void ReadDocumentInfoFromBinaryFile(DocumentInfo* info, FILE* file);

#endif
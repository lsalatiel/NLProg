#ifndef DOCUMENT_INFO_H
#define DOCUMENT_INFO_H

typedef struct DocumentInfo DocumentInfo;

/**
 * @brief allocates space and initialize a document info structure
 * 
 * @return DocumentInfo* 
 */
DocumentInfo* AllocateDocumentInfo();

/**
 * @brief frees memory allocatd for a document info
 * 
 * @param info 
 */
void FreeDocumentInfo(DocumentInfo* info);

/**
 * @brief reallocates space fora a document info array
 * 
 * @param info_array 
 * @param curr_size 
 * @param max_size 
 * @return DocumentInfo** 
 */
DocumentInfo** ReallocDocumentInfoArray(DocumentInfo** info_array, int curr_size, int max_size);

/**
 * @brief updates the information of a document
 * 
 * @param info_array 
 * @param info_size 
 * @param word_index 
 * @return DocumentInfo** 
 */
DocumentInfo** AddDocumentInfo(DocumentInfo** info_array, int info_size, int word_index);

/**
 * @brief returns the word index of a document_info
 * 
 * @param info 
 * @return int 
 */
int GetWordIndexInfo(DocumentInfo* info);

/**
 * @brief updates the word_frequency variable (adds one)
 * 
 * @param info 
 * @return DocumentInfo* 
 */
DocumentInfo* AddWordFrequency(DocumentInfo* info);

/**
 * @brief stores tf_idf of a word in a specific document to the document_info
 * 
 * @param info 
 * @param document_quantity 
 * @param word_appearance 
 * @return DocumentInfo* 
 */
DocumentInfo* StoreTf_idfFromDocumentInfo(DocumentInfo* info, int document_quantity, int word_appearance);

/**
 * @brief saves a document_info structure in a binary file
 * 
 * @param info 
 * @param file 
 */
void SaveDocumentInfoInBinary(DocumentInfo* info, FILE* file);

#endif
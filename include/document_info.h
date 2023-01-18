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
DocumentInfo** ReallocDocumentInfoArray(DocumentInfo** infoArray, int currentSize, int maximumSize);

/**
 * @brief updates the information of a document
 */
DocumentInfo** AddDocumentInfo(DocumentInfo** infoArray, int infoSize, int wordIndex);

/**
 * @brief returns the wordIndex of a documentInfo
 */
int GetWordIndexInfo(DocumentInfo* info);

/**
 * @brief updates the wordFrequency variable (adds one)
 */
DocumentInfo* AddWordFrequency(DocumentInfo* info);

/**
 * @brief stores TFIDF of a word in a specific document to the documentInfo
 */
DocumentInfo* StoreTFIDFFromDocumentInfo(DocumentInfo* info, int documentQuantity, int wordAppearance);

/**
 * @brief writes a documentInfo structure in a binary file
 */
void WriteDocumentInfoInBinaryFile(DocumentInfo* info, FILE* file);

/**
 * @brief reads a document info structure from a binary file
 */
void ReadDocumentInfoFromBinaryFile(DocumentInfo* info, FILE* file);

#endif
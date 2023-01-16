#ifndef FORWARD_INDEX_H
#define FORWARD_INDEX_H

typedef struct ForwardIndex ForwardIndex;

/**
 * @brief allocates and initialize the information of a single forward index
 *
 * @return ForwardIndex*
 */
ForwardIndex* AllocateDocument();

/**
 * @brief frees memory allocated for a single document
 *
 * @param documents
 */
void FreeDocument(ForwardIndex* document);

/**
 * @brief reads and stores name and class of documents
 *
 * @param documents
 * @param train
 * @param documents_size
 * @param documents_alloc
 * @return ForwardIndex**
 */
ForwardIndex** ReadDocuments(ForwardIndex** documents, FILE* train, int* documents_size, int* documents_alloc);

/**
 * @brief reallocates space for the information of a forward index array
 *
 * @param documents
 * @param documents_alloc
 * @return ForwardIndex**
 */
ForwardIndex** ReallocDocuments(ForwardIndex** documents, int* documents_alloc);

/**
 * @brief returns the file_name of a document
 *
 * @param document
 * @return char*
 */
char* GetFileName(ForwardIndex* document);

/**
 * @brief stores the information of a single forward index
 *
 * @param document
 * @param word_index
 * @return ForwardIndex*
 */
ForwardIndex* StoreWordInfoForwardIndex(ForwardIndex* document, int word_index);

/**
 * @brief stores information of a word that is already stored in the document_info array
 *
 * @param document
 * @param word_index
 * @return ForwardIndex*
 */
ForwardIndex* AddWordFrequencyToForwardIndex(ForwardIndex* document, int word_index);

/**
 * @brief stores tf_idf of a word stored in the document_info array
 *
 * @param documents
 * @param word_index
 * @param document_quantity
 * @param word_appearance
 * @return ForwardIndex**
 */
ForwardIndex** StoreTf_idfFromDocuments(ForwardIndex** documents, int word_index, int document_quantity, int word_appearance);

/**
 * @brief saves a forward index in a binary file
 *
 * @param document
 * @param file
 */
void WriteForwardIndexInBinaryFile(ForwardIndex* document, FILE* file);

ForwardIndex* ReadForwardIndexFromBinaryFile(ForwardIndex* document, FILE* file);

#endif
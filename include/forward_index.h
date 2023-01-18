#ifndef FORWARD_INDEX_H
#define FORWARD_INDEX_H

typedef struct ForwardIndex ForwardIndex;

/**
 * @brief allocates and initialize the information of a single forward index
 */
ForwardIndex* AllocDocument();

/**
 * @brief frees memory allocated for a single document
 */
void FreeDocument(ForwardIndex* document);

/**
 * @brief reads and stores name and class of documents
 */
ForwardIndex** ReadDocuments(ForwardIndex** documents, FILE* train, int* documents_size, int* documents_alloc);

/**
 * @brief reallocates space for the information of a forward index array
 */
ForwardIndex** ReallocDocuments(ForwardIndex** documents, int* documents_alloc);

/**
 * @brief returns the fileName of a document
 */
char* GetFileName(ForwardIndex* document);

/**
 * @brief stores the information of a single forward index
 */
ForwardIndex* StoreWordInfoForwardIndex(ForwardIndex* document, int word_index);

/**
 * @brief stores information of a word that is already stored in the document_info array
 */
ForwardIndex* AddWordFrequencyToForwardIndex(ForwardIndex* document, int word_index);

/**
 * @brief stores tf_idf of a word stored in the document_info array
 */
ForwardIndex** StoreTFIDFFromDocuments(ForwardIndex** documents, int word_index, int document_quantity, int word_appearance);

/**
 * @brief writes a forward index in a binary file
 */
void WriteForwardIndexInBinaryFile(ForwardIndex* document, FILE* file);

/**
 * @brief reads a forward index from a binary file
 */
ForwardIndex* ReadForwardIndexFromBinaryFile(ForwardIndex* document, FILE* file);

/**
 * @brief sorts documents array based on TF-IDF with qsort()
 */
void SortTFIDFs(ForwardIndex** documents, int documents_size);

/**
 * @brief comparison function to qsort()
 */
int CompareTFIDFs(const void* a, const void* b);

/**
 * @brief add a single TF-IDF to the document TF-IDF sum
 */
void AddTFIDFToSum(ForwardIndex* document, float add);

/**
 * @brief print the most relevant news based on user given sentence
 */
void PrintNewsResults(ForwardIndex** documents);

/**
 * @brief sets all documents TF-IDFS to zero for a new search
 */
void ResetTFIDFSums(ForwardIndex** documents, int documents_size);

#endif
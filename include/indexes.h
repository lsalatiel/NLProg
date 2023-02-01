#ifndef INDEXES_H
#define INDEXES_H

typedef struct Indexes Indexes;

/**
 * @brief reads main file which it contains the other files
 */
Indexes* ReadTrainFile(Indexes* indexes, char* argv);

/**
 * @brief allocates memory for the inverted and forward indexes
 */
Indexes* AllocateIndexes();

/**
 * @brief frees memory from indexes
 */
void FreeIndexes(Indexes* indexes);

/**
 * @brief opens the texts files
 */
Indexes* ReadInfo(Indexes* indexes, char* argv);

/**
 * @brief reads the texts files and store the information in the inverted index struct
 */
Indexes* CreateIndexesFromFile(Indexes* indexes, FILE* file, int documentIndex);

/**
 * @brief stores the TFIDF of each word of the inverted index in the indexes structure
 */
Indexes* StoreTFIDFFromIndexes(Indexes* indexes);

/**
 * @brief writes indexes in a binary file
 */
void WriteIndexesInBinaryFile(Indexes* indexes, char* argv);

/**
 * @brief reads indexes in a binary file
 */
Indexes* ReadIndexesFromBinaryFile(Indexes* indexes, char* argv);

/**
 * @brief shows the most relevant documents from user given words
 */
void SearchAndSortNews(Indexes* indexes);

/**
 * @brief shows informations about a given word by the user
 */
void GenerateWordRelatory(Indexes* indexes);

/**
 * @brief reset indexes array to the original reading order
 */
void ResetIndexesArrayOrder(Indexes* indexes);

/**
 * @brief shows informations about the documents
 */
void GenerateDocumentRelatory(Indexes* indexes);

/**
 * @brief shows the most probably class of a text
 */
void SortNews(Indexes* indexes, int newsQuantity);

/**
 * @brief returns the most frequent class of a document array
 */
char* FindMostFrequentDocumentClass(Indexes* indexes, int size);

/**
 * @brief generates the output message info for program 1
 */
void GenerateOutputInfo(Indexes* indexes, char* argv);

#endif
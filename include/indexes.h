#ifndef FIRST_PROGRAM_H
#define FIRST_PROGRAM_H

typedef struct Indexes Indexes;

/**
 * @brief reads main file which it contains the other files
 *
 * @param indexes
 * @param argv
 * @return Indexes*
 */
Indexes* ReadTrainFile(Indexes* indexes, char** argv);

/**
 * @brief allocates memory for the inverted and forward indexes
 * @return Indexes*
 */
Indexes* AllocateIndexes();

/**
 * @brief frees memory from indexes
 *
 * @param indexes
 */
void FreeIndexes(Indexes* indexes);

/**
 * @brief opens the texts files
 *
 * @param indexes
 * @return Indexes*
 */
Indexes* ReadInfo(Indexes* indexes);

/**
 * @brief reads the texts files and store the information in the inverted index struct
 *
 * @param indexes
 * @param file
 * @param document_index
 * @return Indexes*
 */
Indexes* CreateIndexesFromFile(Indexes* indexes, FILE* file, int document_index);

/**
 * @brief stores the tf_idf of each word of the inverted index in the indexes structure
 *
 * @param indexes
 * @return Indexes*
 */
Indexes* StoreTf_idfFromIndexes(Indexes* indexes);

/**
 * @brief saves indexes in a binary file
 *
 * @param indexes
 * @param file_name
 */
void WriteIndexesInBinaryFile(Indexes* indexes, char* file_name);

Indexes* ReadIndexesFromBinaryFile(Indexes* indexes, char* file_name);

#endif
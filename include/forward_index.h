#ifndef FORWARD_INDEX_H
#define FORWARD_INDEX_H

typedef struct forward_index_t forward_index_t;

forward_index_t** readDocumentsAndCreateForwardIndexes(FILE* file);

/**
 * @brief allocate space for an array of forward indexes
 * 
 * @param max_size 
 * @return forward_index_t** 
 */
forward_index_t** initializeForwardIndexes(int max_size);

/**
 * @brief create a forward index from parameters
 * 
 * @param document 
 * @param name 
 * @param class
 */
void createForwardIndex(forward_index_t* document, char* name, char* class);

/**
 * @brief 
 * 
 * @param forward_indexes 
 * @param curr_size 
 * @param max_size 
 * @return forward_index_t** 
 */
forward_index_t** reallocForwardIndexes(forward_index_t** forward_indexes, int curr_size, int max_size);

void printDocuments(forward_index_t** forward_indexes, int curr_size);

/**
 * @brief free memory allocated for the forward indexes
 * 
 * @param forward_indexes 
 * @param curr_size 
 */
void freeForwardIndexes(forward_index_t** forward_indexes, int curr_size);

#endif
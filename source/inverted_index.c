#include "libraries.h"

struct inverted_index_t {
    char* word;
    int curr_size; // number of times that the word appeared in a document. it determines the size of the info array
    int max_size; // maximum size of the info array
    word_info_t** info; /* stores the indexes of documents which contain the word, the frequency of each word appears in the document,
                            and its tf_idf */ // depois pode apagar isso aqui, eh so pra gente ter uma nocao doq ta acontecendo
                            // ainda nao tenho certeza se eh isso mesmo tbm
};

inverted_index_t* createInvertedIndex(char* word) {
    inverted_index_t* index = malloc(sizeof(inverted_index_t));

    index->word = word;
    
    index->curr_size = 0;
    index->max_size = 10;

    index->info = createWordInfo(index->curr_size, index->max_size);

    return index;
}
#include "libraries.h"

struct word_info_t {
    int document_index;
    int frequency;
    int tf_idf;
};

/*word_info_t** createWordInfo(int curr_size, int max_size) {
    word_info_t** word_info = malloc(sizeof(word_info_t*) * max_size);

    for(int i = 0; i < max_size; i++) {
        word_info[i] = malloc(sizeof(word_info));
    }

    return word_info;
}*/
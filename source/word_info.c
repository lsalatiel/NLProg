#include "libraries.h"

typedef struct {
    int document_index;
    int frequency;
    int tf_idf;
} word_info;

word_info** createWordInfo(int curr_size, int max_size) {
    word_info** word_info = malloc(sizeof(word_info_t*) * max_size);

    for(int i = 0; i < max_size; i++) {
        word_info[i] = malloc(sizeof(word_info));
    }

    return word_info;
}
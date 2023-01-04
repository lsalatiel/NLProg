#include "libraries.h"

struct forward_index_t {
    char* name;
    char class[3];
    int curr_size;
    int max_size;
    document_info_t** info;
};

void readDocumentsAndCreateForwardIndexes(FILE* file) {
    if(file == NULL) {
        return;
    }

    createForwardIndexes();
}
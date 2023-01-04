#include "libraries.h"

#define MAX_FILE_NAME_LENGTH 200
#define MAX_CLASS_NAME_LENGTH 4

struct forward_index_t {
    char* name;
    char* class;
    int curr_size;
    int max_size;
    document_info_t** info;
};


// essa funcao talvez tenha que ficar em outra struct qeu tenha um array de forward e um de inverted index tipo a do spotfes que tu tinha falado
// mas fora isso, por enquanto ela ta armazenando o nome e a classe de todos os arquivos certin
forward_index_t** readDocumentsAndCreateForwardIndexes(FILE* file) {
    if(file == NULL) {
        return NULL;
    }

    int curr_size = 0;
    int max_size = 10;

    forward_index_t** forward_indexes = initializeForwardIndexes(max_size);

    char name[MAX_FILE_NAME_LENGTH];
    name[0] = '\0';
    char class[MAX_CLASS_NAME_LENGTH];
    class[0] = '\0';

    while(!feof(file)) {
        resetString(name);
        resetString(class);

        fscanf(file, "%s", name);
        if(name[0] == '\0')
            break;
    
        fscanf(file, "%s", class);

        if(curr_size == max_size) {
            max_size *= 2;
            forward_indexes = reallocForwardIndexes(forward_indexes, curr_size, max_size);
        }

        //forward_indexes[curr_size] = malloc(sizeof(forward_index_t)); ou a gente da malloc aqui toda hora ou da tudo de uma vez na funcao de realloc
            
        createForwardIndex(forward_indexes[curr_size], name, class);

        curr_size++;
    }

    printDocuments(forward_indexes, curr_size);

    return forward_indexes;
}

forward_index_t** initializeForwardIndexes(int max_size) {
    forward_index_t** forward_indexes = malloc(max_size * sizeof(forward_index_t*));

    for(int i = 0; i < max_size; i++) {
        forward_indexes[i] = malloc(sizeof(forward_index_t));
    }

    return forward_indexes;
}

void createForwardIndex(forward_index_t* document, char* name, char* class) {
    document->name = strdup(name);
    document->class = strdup(class);
}

forward_index_t** reallocForwardIndexes(forward_index_t** forward_indexes, int curr_size, int max_size) {
    forward_indexes = realloc(forward_indexes, max_size * sizeof(forward_index_t*));

    for(int i = curr_size; i < max_size; i++) {
        forward_indexes[i] = malloc(sizeof(forward_index_t));
    }

    return forward_indexes;
}

void printDocuments(forward_index_t** forward_indexes, int curr_size) {
    for(int i = 0; i < curr_size; i++) {
        printf("%s\n", forward_indexes[i]->name);
        printf("%s\n\n", forward_indexes[i]->class);
    }
}

void freeForwardIndexes(forward_index_t** forward_indexes, int curr_size) {
    for(int i = 0; i < curr_size; i++) {
        free(forward_indexes[i]->name);
        free(forward_indexes[i]->class);
        free(forward_indexes[i]);
    }

    free(forward_indexes);
}

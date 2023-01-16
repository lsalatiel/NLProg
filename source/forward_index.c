#include "libraries.h"

struct ForwardIndex {
    int index;
    char* name;
    char* class;
    DocumentInfo** info;
    int* info_size;
    int* info_alloc;
};

ForwardIndex* AllocateDocument() {
    ForwardIndex* document = NULL;

    document = calloc(sizeof(ForwardIndex), 1);
    document->info = malloc(STARTER_ALLOC * sizeof(DocumentInfo*));
    document->info_size = malloc(sizeof(int));
    document->info_alloc = malloc(sizeof(int));
    *document->info_size = 0;
    *document->info_alloc = STARTER_ALLOC;

    for (int x = 0; x < STARTER_ALLOC; x++) {
        document->info[x] = AllocateDocumentInfo();
    }

    return document;
}

void FreeDocument(ForwardIndex* document) {
    for (int x = 0; x < *document->info_alloc; x++) {
        FreeDocumentInfo(document->info[x]);
    }

    FreeAndNull(document->name);
    FreeAndNull(document->class);
    FreeAndNull(document->info);
    FreeAndNull(document->info_size);
    FreeAndNull(document->info_alloc);
    FreeAndNull(document);
}

ForwardIndex** ReadDocuments(ForwardIndex** documents, FILE* train, int* documents_size, int* documents_alloc) {
    char* buffer = malloc(BUFFER_SIZE * sizeof(char));

    for (int x = 0; fgets(buffer, BUFFER_SIZE, train) && !EndOfFile(buffer[0]); x++) {
        *documents_size = x + 1;

        if (*documents_size > *documents_alloc) {
            *documents_alloc *= 2;
            documents = ReallocDocuments(documents, documents_alloc);
        }

        documents[x]->index = x;
        documents[x]->name = strdup(strtok(buffer, " "));
        documents[x]->class = strdup(strtok(NULL, "\n"));
    }

    FreeAndNull(buffer);

    return documents;
}

ForwardIndex** ReallocDocuments(ForwardIndex** documents, int* documents_alloc) {
    ForwardIndex** new = NULL;
    new = realloc(documents, *documents_alloc * sizeof(ForwardIndex*));
    documents = new;

    for (int x = *documents_alloc / 2; x < *documents_alloc; x++) {
        documents[x] = AllocateDocument();
    }

    return documents;
}

char* GetFileName(ForwardIndex* document) {
    return document->name;
}

ForwardIndex* StoreWordInfoForwardIndex(ForwardIndex* document, int word_index) {
    // cada palavra nova eh uma posicao nova do array de info
    if (*document->info_size == *document->info_alloc) {
        *document->info_alloc *= 2;
        document->info = ReallocDocumentInfoArray(document->info, *document->info_size, *document->info_alloc);
    }

    document->info = AddDocumentInfo(document->info, *document->info_size, word_index);
    (*document->info_size)++;

    return document;
}

ForwardIndex* AddWordFrequencyToForwardIndex(ForwardIndex* document, int word_index) {
    for (int i = 0; i < *document->info_size; i++) {
        if (GetWordIndexInfo(document->info[i]) == word_index) {
            document->info[i] = AddWordFrequency(document->info[i]);
            break;
        }
    }

    return document;
}

ForwardIndex** StoreTf_idfFromDocuments(ForwardIndex** documents, int word_index, int document_quantity, int word_appearance) {
    int word_check = 0;

    for (int i = 0; i < document_quantity; i++) {
        for (int j = 0; j < *documents[i]->info_size; j++) {
            if (GetWordIndexInfo(documents[i]->info[j]) == word_index) {
                documents[i]->info[j] = StoreTf_idfFromDocumentInfo(documents[i]->info[j], document_quantity, word_appearance);
                word_check++;
            }
        }
    }

    return documents;
}

void WriteForwardIndexInBinaryFile(ForwardIndex* document, FILE* file) {
    if (file == NULL) {
        return;
    }

    fwrite(&document->index, sizeof(int), 1, file);
    int name_size = strlen(document->name) + 1;
    fwrite(&name_size, sizeof(int), 1, file);
    fwrite(document->name, sizeof(char), name_size, file);
    int class_size = strlen(document->class) + 1;
    fwrite(&class_size, sizeof(int), 1, file);
    fwrite(document->class, sizeof(char), class_size, file);
    fwrite(document->info_size, sizeof(int), 1, file);
    fwrite(document->info_alloc, sizeof(int), 1, file);

    for (int i = 0; i < *document->info_size; i++) {
        WriteDocumentInfoInBinaryFile(document->info[i], file);
    }
}

ForwardIndex* ReadForwardIndexFromBinaryFile(ForwardIndex* document, FILE* file) {
    if (file == NULL) {
        return NULL;
    }

    fread(&document->index, sizeof(int), 1, file);
    int name_size;
    fread(&name_size, sizeof(int), 1, file);
    document->name = malloc(name_size * sizeof(char));
    fread(document->name, sizeof(char), name_size, file);
    int class_size;
    fread(&class_size, sizeof(int), 1, file);
    document->class = malloc(class_size * sizeof(char));
    fread(document->class, sizeof(char), class_size, file);
    fread(document->info_size, sizeof(int), 1, file);
    fread(document->info_alloc, sizeof(int), 1, file);

    if (*document->info_alloc > STARTER_ALLOC) {
        document->info = ReallocDocumentInfoArray(document->info, STARTER_ALLOC, *document->info_alloc);
    }

    for (int i = 0; i < *document->info_size; i++) {
        ReadDocumentInfoFromBinaryFile(document->info[i], file);
    }

    return document;
}
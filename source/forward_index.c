#include "libraries.h"

struct ForwardIndex {
    int index;
    char* name;
    char* class;
    DocumentInfo** info;
    int* info_size;
    int* info_alloc;
    float* sum_tf_idf;
};

void AddTFIDFToSum(ForwardIndex* document, float add) {
    *document->sum_tf_idf += add;
}

ForwardIndex* AllocDocument() {
    ForwardIndex* document = NULL;

    document = calloc(sizeof(ForwardIndex), 1);
    document->info = malloc(STARTER_ALLOC * sizeof(DocumentInfo*));
    document->info_size = calloc(sizeof(int), 1);
    document->info_alloc = malloc(sizeof(int));
    document->sum_tf_idf = calloc(sizeof(float), 1);
    *document->info_alloc = STARTER_ALLOC;

    for (int x = 0; x < STARTER_ALLOC; x++) {
        document->info[x] = AllocDocumentInfo();
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
    FreeAndNull(document->sum_tf_idf);
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
        documents[x] = AllocDocument();
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

ForwardIndex** StoreTFIDFFromDocuments(ForwardIndex** documents, int word_index, int document_quantity, int word_appearance) {
    int word_check = 0;

    for (int i = 0; i < document_quantity; i++) {
        for (int j = 0; j < *documents[i]->info_size; j++) {
            if (GetWordIndexInfo(documents[i]->info[j]) == word_index) {
                documents[i]->info[j] = StoreTFIDFFromDocumentInfo(documents[i]->info[j], document_quantity, word_appearance);
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

void SortTFIDFs(ForwardIndex** documents, int documents_size) {
    qsort(documents, documents_size, sizeof(ForwardIndex*), CompareTFIDFs);
}

void ResetTFIDFSums(ForwardIndex** documents, int documents_size) {
    for (int x = 0; x < documents_size; x++) {
        *documents[x]->sum_tf_idf = 0.0;
    }
}

int CompareTFIDFs(const void* a, const void* b) {
    float* sum_tf_idf_a = (*(const ForwardIndex**)a)->sum_tf_idf;
    float* sum_tf_idf_b = (*(const ForwardIndex**)b)->sum_tf_idf;

    if (*sum_tf_idf_a > *sum_tf_idf_b)
        return -1;
    else if (*sum_tf_idf_a < *sum_tf_idf_b)
        return 1;
    else
        return 0;
}

void PrintNewsResults(ForwardIndex** documents) {
    bool nothingPrinted = true;
    printf("\n");

    for (int x = 0; x < RESULTS_NUMBER; x++) {
        if (*documents[x]->sum_tf_idf != 0) {
            printf("Document name: %s ∙ TF-IDF: %.2f\n", documents[x]->name, *documents[x]->sum_tf_idf);
            nothingPrinted = false;
        }
    }

    if (nothingPrinted) {
        RedText();
        printf("No news found.\n");
        DefaultText();
    }

    printf("\n");
}
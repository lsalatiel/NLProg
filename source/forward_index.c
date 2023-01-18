#include "libraries.h"

struct ForwardIndex {
    int index;
    char* name;
    char* class;
    DocumentInfo** info;
    int* infoSize;
    int* infoAlloc;
    float* sumTFIDF;
};

int CompareDocumentsIndex(const void* a, const void* b) {
    return (*(ForwardIndex**)a)->index - (*(ForwardIndex**)b)->index;
}

char* GetDocumentClass(ForwardIndex* document) {
    return document->class;
}

void AddTFIDFToSum(ForwardIndex* document, float add) {
    *document->sumTFIDF += add;
}

ForwardIndex* AllocDocument() {
    ForwardIndex* document = NULL;

    document = calloc(sizeof(ForwardIndex), 1);
    document->info = malloc(STARTER_ALLOC * sizeof(DocumentInfo*));
    document->infoSize = calloc(sizeof(int), 1);
    document->infoAlloc = malloc(sizeof(int));
    document->sumTFIDF = calloc(sizeof(float), 1);
    *document->infoAlloc = STARTER_ALLOC;

    for (int x = 0; x < STARTER_ALLOC; x++) {
        document->info[x] = AllocDocumentInfo();
    }

    return document;
}

void FreeDocument(ForwardIndex* document) {
    for (int x = 0; x < *document->infoAlloc; x++) {
        FreeDocumentInfo(document->info[x]);
    }

    FreeAndNull(document->name);
    FreeAndNull(document->class);
    FreeAndNull(document->info);
    FreeAndNull(document->infoSize);
    FreeAndNull(document->infoAlloc);
    FreeAndNull(document->sumTFIDF);
    FreeAndNull(document);
}

ForwardIndex** ReadDocuments(ForwardIndex** documents, FILE* train, int* documentsSize, int* documentsAlloc) {
    char* buffer = malloc(BUFFER_SIZE * sizeof(char));

    for (int x = 0; fgets(buffer, BUFFER_SIZE, train) && !EndOfFile(buffer[0]); x++) {
        *documentsSize = x + 1;

        if (*documentsSize > *documentsAlloc) {
            *documentsAlloc *= 2;
            documents = ReallocDocuments(documents, documentsAlloc);
        }

        documents[x]->index = x;
        documents[x]->name = strdup(strtok(buffer, " "));
        documents[x]->class = strdup(strtok(NULL, "\n"));
    }

    FreeAndNull(buffer);

    return documents;
}

ForwardIndex** ReallocDocuments(ForwardIndex** documents, int* documentsAlloc) {
    ForwardIndex** new = NULL;
    new = realloc(documents, *documentsAlloc * sizeof(ForwardIndex*));
    documents = new;

    for (int x = *documentsAlloc / 2; x < *documentsAlloc; x++) {
        documents[x] = AllocDocument();
    }

    return documents;
}

char* GetFileName(ForwardIndex* document) {
    return document->name;
}

ForwardIndex* StoreWordInfoForwardIndex(ForwardIndex* document, int wordIndex) {
    // cada palavra nova eh uma posicao nova do array de info
    if (*document->infoSize == *document->infoAlloc) {
        *document->infoAlloc *= 2;
        document->info = ReallocDocumentInfoArray(document->info, *document->infoSize, *document->infoAlloc);
    }

    document->info = AddDocumentInfo(document->info, *document->infoSize, wordIndex);
    (*document->infoSize)++;

    return document;
}

ForwardIndex* AddWordFrequencyToForwardIndex(ForwardIndex* document, int wordIndex) {
    for (int i = 0; i < *document->infoSize; i++) {
        if (GetWordIndexInfo(document->info[i]) == wordIndex) {
            document->info[i] = AddWordFrequency(document->info[i]);
            break;
        }
    }

    return document;
}

ForwardIndex** StoreTFIDFFromDocuments(ForwardIndex** documents, int wordIndex, int documentQuantity, int wordAppearance) {
    int wordCheck = 0;

    for (int i = 0; i < documentQuantity; i++) {
        for (int j = 0; j < *documents[i]->infoSize; j++) {
            if (GetWordIndexInfo(documents[i]->info[j]) == wordIndex) {
                documents[i]->info[j] = StoreTFIDFFromDocumentInfo(documents[i]->info[j], documentQuantity, wordAppearance);
                wordCheck++;
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
    int nameSize = strlen(document->name) + 1;
    fwrite(&nameSize, sizeof(int), 1, file);
    fwrite(document->name, sizeof(char), nameSize, file);
    int classSize = strlen(document->class) + 1;
    fwrite(&classSize, sizeof(int), 1, file);
    fwrite(document->class, sizeof(char), classSize, file);
    fwrite(document->infoSize, sizeof(int), 1, file);
    fwrite(document->infoAlloc, sizeof(int), 1, file);

    for (int i = 0; i < *document->infoSize; i++) {
        WriteDocumentInfoInBinaryFile(document->info[i], file);
    }
}

ForwardIndex* ReadForwardIndexFromBinaryFile(ForwardIndex* document, FILE* file) {
    if (file == NULL) {
        return NULL;
    }

    fread(&document->index, sizeof(int), 1, file);
    int nameSize;
    fread(&nameSize, sizeof(int), 1, file);
    document->name = malloc(nameSize * sizeof(char));
    fread(document->name, sizeof(char), nameSize, file);
    int classSize;
    fread(&classSize, sizeof(int), 1, file);
    document->class = malloc(classSize * sizeof(char));
    fread(document->class, sizeof(char), classSize, file);
    fread(document->infoSize, sizeof(int), 1, file);
    fread(document->infoAlloc, sizeof(int), 1, file);

    if (*document->infoAlloc > STARTER_ALLOC) {
        document->info = ReallocDocumentInfoArray(document->info, STARTER_ALLOC, *document->infoAlloc);
    }

    for (int i = 0; i < *document->infoSize; i++) {
        ReadDocumentInfoFromBinaryFile(document->info[i], file);
    }

    return document;
}

void ResetTFIDFSums(ForwardIndex** documents, int documentsSize) {
    for (int x = 0; x < documentsSize; x++) {
        *documents[x]->sumTFIDF = 0.0;
    }
}

int GetDocumentsWithTFIDFNumber(ForwardIndex** documents, int documentsSize) {
    int x = 0;

    for (x = 0; x < documentsSize; x++) {
        if (*documents[x]->sumTFIDF == 0.0) {
            break;
        }
    }

    return x;
}

int CompareTFIDFs(const void* a, const void* b) {
    float* sumTFIDFx = (*(const ForwardIndex**)a)->sumTFIDF;
    float* sumTFIDFy = (*(const ForwardIndex**)b)->sumTFIDF;

    if (*sumTFIDFx > *sumTFIDFy)
        return -1;
    else if (*sumTFIDFx < *sumTFIDFy)
        return 1;
    else
        return 0;
}

void PrintNewsResults(ForwardIndex** documents, int results) {
    GreenText();
    if (results == 1) {
        printf("1 news was found with the searched term:\n\n");
    } else if (results <= 10) {
        printf("%d news were found with the searched term:\n\n", results);
    } else if (results > 10) {
        printf("Showing the 10 most relevant news for the searched term:\n\n");
    }

    for (int x = 0; x < MAX_RESULTS_NUMBER; x++) {
        if (*documents[x]->sumTFIDF == 0.0) {
            break;
        }

        printf("Document name: %s ∙ TF-IDF: %.2f\n", documents[x]->name, *documents[x]->sumTFIDF);
    }
    DefaultText();
}

void PrintDocumentWordResults(ForwardIndex* document, int order) {
    GreenText();
    printf("%dº document with most appearances: %s\n", order, document->name);
    DefaultText();
}

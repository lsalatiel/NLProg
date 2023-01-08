#ifndef FORWARD_INDEX_H
#define FORWARD_INDEX_H

typedef struct ForwardIndex ForwardIndex;

ForwardIndex* AllocateDocuments();
void FreeDocuments(ForwardIndex* documents);
ForwardIndex** ReadDocuments(ForwardIndex** documents, FILE* train, int* documents_size, int* documents_alloc);
ForwardIndex** ReallocDocuments(ForwardIndex** documents, int* documents_alloc);
char* GetFileName(ForwardIndex* document);

#endif
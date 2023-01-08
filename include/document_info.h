#ifndef DOCUMENT_INFO_H
#define DOCUMENT_INFO_H

typedef struct DocumentInfo DocumentInfo;

DocumentInfo* AllocateDocumentsInfo();
void FreeDocumentsInfo(DocumentInfo* info);

#endif
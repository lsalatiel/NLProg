#ifndef DOCUMENT_INFO_H
#define DOCUMENT_INFO_H

typedef struct DocumentInfo DocumentInfo;

DocumentInfo* AllocateDocumentInfo();
void FreeDocumentInfo(DocumentInfo* info);

DocumentInfo** ReallocDocumentInfoArray(DocumentInfo** info_array, int curr_size, int max_size);

DocumentInfo** AddDocumentInfo(DocumentInfo** info_array, int info_size, int word_index);

int GetWordIndexInfo(DocumentInfo* info);

DocumentInfo* AddWordFrequency(DocumentInfo* info);

DocumentInfo* StoreTf_idfFromDocumentInfo(DocumentInfo* info, int document_quantity, int word_appearance);

#endif
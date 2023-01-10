#ifndef WORD_INFO_H
#define WORD_INFO_H

typedef struct WordInfo WordInfo;

WordInfo* AllocateWordInfo(WordInfo* info);

//WordInfo* ReallocWordInfo(WordInfo* info, int size);

void FreeWordInfo(WordInfo* info);

WordInfo** AddWordInfo(WordInfo** info_array, int info_size, int document_index);

WordInfo* AddDocumentFrequency(WordInfo* info);

int GetDocumentIndexInfo(WordInfo* info);

#endif
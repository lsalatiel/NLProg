#ifndef WORD_INFO_H
#define WORD_INFO_H

typedef struct WordInfo WordInfo;

WordInfo* AllocateWordInfo(WordInfo* info);

//WordInfo* ReallocWordInfo(WordInfo* info, int size);

void FreeWordInfo(WordInfo* info);

WordInfo* AddDocumentFrequency(WordInfo** info, int document_index);

#endif
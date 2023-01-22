#ifndef TEXT_INFO_H
#define TEXT_INFO_H

typedef struct TextInfo TextInfo;

TextInfo** AllocateTextInfoArray(TextInfo** text, int textAlloc);

TextInfo* AllocText(TextInfo* textInfo);

TextInfo** ReallocText(TextInfo** text, int textAlloc);

void FreeTextInfo(TextInfo* textInfo);

TextInfo* StoreTextInfo(TextInfo* textInfo, char* word);

TextInfo* AddFrequencyTextInfo(TextInfo* textInfo);

int GetWordIndexInText(TextInfo** text, int text_size, char* word);

char* GetWordFromText(TextInfo* textInfo);

TextInfo* StoreTFIDFTextInfo(TextInfo* textInfo, int documentQuantity, int wordAppearence);

float GetTFIDFTextInfo(TextInfo* textInfo);

#endif
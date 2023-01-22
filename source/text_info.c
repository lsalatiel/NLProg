#include "libraries.h"

struct TextInfo {
    char* word;
    int frequency;
    float tf_idf;
};

TextInfo* AllocText(TextInfo* textInfo) {
    textInfo = calloc(sizeof(TextInfo), 1);
    textInfo->frequency = 0;
    textInfo->tf_idf = -1;

    return textInfo;
}

TextInfo** ReallocText(TextInfo** text, int textAlloc) {
    TextInfo** new = NULL;
    new = realloc(text, textAlloc * sizeof(TextInfo*));
    text = new;

    for (int x = textAlloc / 2; x < textAlloc; x++) {
        text[x] = AllocText(text[x]);
    }

    return text;
}

TextInfo* StoreTextInfo(TextInfo* textInfo, char* word) {
    textInfo->word = strdup(word);
    textInfo->frequency++;

    return textInfo;
}

TextInfo* AddFrequencyTextInfo(TextInfo* textInfo) {
    textInfo->frequency++;

    return textInfo;
}

int GetWordIndexInText(TextInfo** text, int text_size, char* word) {
    for(int i = 0; i < text_size; i++) {
        if(strcmp(text[i]->word, word) == 0)
            return i;
    }
    
    return -1;
}

char* GetWordFromText(TextInfo* textInfo) {
    return textInfo->word;
}

TextInfo* StoreTFIDFTextInfo(TextInfo* textInfo, int documentQuantity, int wordAppearence) {
    textInfo->tf_idf = CalculateTFIDF(textInfo->frequency, documentQuantity, wordAppearence);

    return textInfo;
}

TextInfo** AllocateTextInfoArray(TextInfo** text, int textAlloc) {
    text = malloc(textAlloc * sizeof(TextInfo*));

    for(int i = 0; i < textAlloc; i++) {
        text[i] = AllocText(text[i]);
    }

    return text;
}

void FreeTextInfo(TextInfo* textInfo) {
    FreeAndNull(textInfo->word);
    FreeAndNull(textInfo);
}

float GetTFIDFTextInfo(TextInfo* textInfo) {
    return textInfo->tf_idf;
}
#include "libraries.h"

struct TextInfo {
    char* word;
    int frequency;
    float tfidf;
};

TextInfo* AllocText(TextInfo* textInfo) {
    textInfo = calloc(1, sizeof(TextInfo));
    textInfo->frequency = 0;
    textInfo->tfidf = -1;

    return textInfo;
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

int GetWordIndexInText(TextInfo** text, int textSize, char* word) {
    for (int i = 0; i < textSize; i++) {
        if (strcmp(text[i]->word, word) == 0)
            return i;
    }

    return -1;
}

char* GetWordFromText(TextInfo* textInfo) {
    return textInfo->word;
}

TextInfo* StoreTFIDFTextInfo(TextInfo* textInfo, int documentQuantity, int wordAppearence) {
    textInfo->tfidf = CalculateTFIDF(textInfo->frequency, documentQuantity, wordAppearence);

    return textInfo;
}

TextInfo** AllocateTextInfoArray(TextInfo** text, int textAlloc) {
    text = malloc(textAlloc * sizeof(TextInfo*));

    for (int i = 0; i < textAlloc; i++)
        text[i] = AllocText(text[i]);

    return text;
}

void FreeTextInfo(TextInfo* textInfo) {
    FreeAndNull(textInfo->word);
    FreeAndNull(textInfo);
}

float GetTFIDFTextInfo(TextInfo* textInfo) {
    return textInfo->tfidf;
}
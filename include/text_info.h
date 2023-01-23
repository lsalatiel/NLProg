#ifndef TEXT_INFO_H
#define TEXT_INFO_H

typedef struct TextInfo TextInfo;

/**
 * @brief allocates space of a textInfo array and each element of the array
 * 
 * @param text 
 * @param textAlloc 
 * @return TextInfo** 
 */
TextInfo** AllocateTextInfoArray(TextInfo** text, int textAlloc);

/**
 * @brief allocates space and initialize the variables of a single textInfo  
 * 
 * @param textInfo 
 * @return TextInfo* 
 */
TextInfo* AllocText(TextInfo* textInfo);

// TextInfo** ReallocText(TextInfo** text, int textAlloc);

/**
 * @brief frees memory allocated for a single textInfo structure
 * 
 * @param textInfo 
 */
void FreeTextInfo(TextInfo* textInfo);

/**
 * @brief stores a word and adds one to the frequency of the textInfo structure
 * 
 * @param textInfo 
 * @param word 
 * @return TextInfo* 
 */
TextInfo* StoreTextInfo(TextInfo* textInfo, char* word);

/**
 * @brief adds one to the frequency when the word is already in the structure
 * 
 * @param textInfo 
 * @return TextInfo* 
 */
TextInfo* AddFrequencyTextInfo(TextInfo* textInfo);

/**
 * @brief returns the index of a word in a textInfo array
 * 
 * @param text 
 * @param textSize 
 * @param word 
 * @return int 
 */
int GetWordIndexInText(TextInfo** text, int textSize, char* word);

/**
 * @brief returns the word of a textInfo structure
 * 
 * @param textInfo 
 * @return char* 
 */
char* GetWordFromText(TextInfo* textInfo);

/**
 * @brief stores the TFIDF of a word in the textInfo structure
 * 
 * @param textInfo 
 * @param documentQuantity 
 * @param wordAppearence 
 * @return TextInfo* 
 */
TextInfo* StoreTFIDFTextInfo(TextInfo* textInfo, int documentQuantity, int wordAppearence);

/**
 * @brief returns the TFIDF of a textInfo structure
 * 
 * @param textInfo 
 * @return float 
 */
float GetTFIDFTextInfo(TextInfo* textInfo);

#endif
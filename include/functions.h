#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/**
 * @brief changes text to bold form
 */
void BoldText();

/**
 * @brief changes text colour to default
 */
void DefaultText();

/**
 * @brief changes text colour to red
 */
void RedText();

/**
 * @brief changes text colour to green
 */
void GreenText();

/**
 * @brief checks if arguments were correctly sent by command line
 */
void CheckDataFilesPath(int argc);

/**
 * @brief prints an error message for not opening a file
 */
void PrintFileError();

/**
 * @brief frees any pointer and set it to NULL
 */
void FreeAndNull(void* pointer);

/**
 * @brief checks if it's end of a file
 */
bool EndOfFile(char character);

/**
 * @brief calculates the TFIDF of each word in a specific document
 */
float CalculateTFIDF(int frequency, int documentQuantity, int wordAppearance);

/**
 * @brief clear the terminal for a better exhibition
 */
void ClearTerminal();

/**
 * @brief reads an integer and checks if it's in an interval defined by parameters
 * @param minimumRange the lower value from a closed interval
 * @param maximumRange the higher value from a closed interval
 * @return a valid integer
 */
int GetValidIntegerInput(int minimumRange, int maximumRange);

/**
 * @brief shows the initial menu and returns the chosen option
 */
int SetUpMainMenu();

/**
 * @brief reads a sentence and put every single word in an individual array
 */
char** GetUserSentenceInput(int* querySize);

/**
 * @brief frees every pointer used in GetUserSentenceInput() function
 */
void ResetUserSearchInput(char** input, int* inputSize);

/**
 * @brief prints an ascii art for better exhibition
 */
void PrintArtMenu();

/**
 * @brief returns a word given by user
 */
char* GetUserWordInput();

int CompareFloats(const void* a, const void* b);

#endif
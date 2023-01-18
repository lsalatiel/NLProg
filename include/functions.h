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
 * @brief calculates the tf_idf of each word in a specific document
 */
float CalculateTf_idf(int frequency, int document_quantity, int word_appearance);

/**
 * @brief clear the terminal for a better exhibition
 */
void ClearTerminal();

/**
 * @brief reads an integer and checks if it's in an interval defined by parameters
 * @param min_range the lower value from a closed interval
 * @param max_range the higher value from a closed interval
 * @return a valid integer
 */
int GetValidIntegerInput(int min_range, int max_range);

/**
 * @brief shows the initial menu and returns the chosen option
 */
int SetUpMainMenu();

/**
 * @brief reads a sentence and put every single word in an individual array
 */
char** GetUserSearchInput(int* query_size);

/**
 * @brief frees every pointer used in GetUserSearchInput() function
 */
void ResetUserSearchInput(char** input, int* input_size);

/**
 * @brief prints an ascii art for better exhibition
 */
void PrintArtMenu();

#endif
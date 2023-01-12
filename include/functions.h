#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/**
 * @brief changes text colour to default
 */
void DefaultTextColour();

/**
 * @brief changes text colour to red
 */
void RedTextColour();

/**
 * @brief checks if arguments were correctly sent by command line
 */
void CheckDataFilesPath(int argc);

/**
 * @brief prints an error message for not oppening a file
 * 
 */
void PrintFileError();

/**
 * @brief frees any pointer and set it to NULL
 * 
 * @param pointer 
 */
void FreeAndNull(void* pointer);

/**
 * @brief checks if it's end of a file
 * 
 * @param character 
 * @return true 
 * @return false 
 */
bool EndOfFile(char character);

int CompareString(const void* a, const void* b);

#endif
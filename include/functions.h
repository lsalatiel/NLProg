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

void PrintFileError();
void FreeAndNull(void* pointer);
bool EndOfFile(char character);

#endif
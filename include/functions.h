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
 * @brief puts a '\0' in all characters of the string
 */
void resetString(char* name);

#endif
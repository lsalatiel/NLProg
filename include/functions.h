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

/**
 * @brief calculates the tf_idf of each word in a specific document
 *
 * @param frequency
 * @param document_quantity
 * @param word_appearance
 * @return float
 */
float CalculateTf_idf(int frequency, int document_quantity, int word_appearance);

void ClearTerminal();

/**
 * @brief lê um número inteiro e verifica se está contido entre um intervalo definido pelos parâmetros
 * @param min_range o menor valor de um intervalo fechado
 * @param max_range o maior valor de um intervalo fechado
 * @return um número válido ou uma mensagem de erro pedindo o input novamente
 */
int GetValidIntegerInput(int min_range, int max_range);

/**
 * @brief exibe o menu
 * @return a opção escolhida no menu
 */
int SetUpMainMenu();

char** GetUserSearchInput(int* query_size);

#endif
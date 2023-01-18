#ifndef CLASSES_H
#define CLASSES_H

typedef struct Classes Classes;

/**
 * @brief allocates space for a class structure
 */
Classes** AllocClasses();

/**
 * @brief frees memory allocated for a class structure
 */
void FreeClasses(Classes** classes);

/**
 * @brief add one unit to class counter
 */
void AddClassCount(Classes* class);

/**
 * @brief returns class name
 */
char* GetClassName(Classes* class);

/**
 * @brief comparison function for qsort() based on descending class appearances order
 */
int CompareClasses(const void* a, const void* b);

/**
 * @brief prints all classes informations
 */
void PrintClasses(Classes** classes);

/**
 * @brief initialize a class structure
 */
void ReadClasses(Classes** classes, char* documentClass);

#endif
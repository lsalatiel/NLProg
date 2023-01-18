#ifndef CLASSES_H
#define CLASSES_H

typedef struct Classes Classes;

Classes** AllocClasses();
void FreeClasses(Classes** classes);
void AddClassCount(Classes* class);
char* GetClassName(Classes* class);

/**
 * @brief comparison function for qsort() based on descending class appearances order
 */
int CompareClasses(const void* a, const void* b);
void PrintClasses(Classes** classes);
void ReadClasses(Classes** classes, char* documentClass);

#endif
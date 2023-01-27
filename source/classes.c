#include "libraries.h"

struct Classes {
    char* class;
    int count;
};

Classes** AllocClasses() {
    Classes** classes = malloc(MAX_CLASSES_NUMBER * sizeof(Classes*));

    for (int x = 0; x < MAX_CLASSES_NUMBER; x++) {
        classes[x] = calloc(sizeof(Classes), 1);
    }

    classes[0]->class = strdup("pot");
    classes[1]->class = strdup("at2");
    classes[2]->class = strdup("cid");
    classes[3]->class = strdup("eco");
    classes[4]->class = strdup("ept");
    classes[5]->class = strdup("poc");
    classes[6]->class = strdup("reg");
    classes[7]->class = strdup("opi");
    classes[8]->class = strdup("int");
    classes[9]->class = strdup("inf");

    return classes;
}

void FreeClasses(Classes** classes) {
    for (int x = 0; x < MAX_CLASSES_NUMBER; x++) {
        FreeAndNull(classes[x]->class);
        FreeAndNull(classes[x]);
    }

    FreeAndNull(classes);
}

void AddClassCount(Classes* class) {
    class->count++;
}

char* GetClassName(Classes* class) {
    return class->class;
}

int CompareClasses(const void* a, const void* b) {
    return (*(const Classes**)b)->count - (*(const Classes**)a)->count;
}

void PrintClasses(Classes** classes) {
    printf("\n");

    for (int x = 0; x < MAX_CLASSES_NUMBER; x++) {
        if (classes[x]->count == 0) {
            break;
        }
        printf(GREEN "In class '%s' appearances: %d\n" DEFAULT, classes[x]->class, classes[x]->count);
    }

    printf("\n");
}

void ReadClasses(Classes** classes, char* documentClass) {
    for (int x = 0; x < MAX_CLASSES_NUMBER; x++) {
        char* class = GetClassName(classes[x]);
        if (strcmp(documentClass, class) == 0) {
            AddClassCount(classes[x]);
            break;
        }
    }
}
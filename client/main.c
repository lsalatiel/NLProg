#include "libraries.h"

int main(int argc, char** argv) {
    // CheckDataFilesPath(argc);

    Indexes* indexes = NULL;
    indexes = AllocateIndexes(indexes);
    indexes = ReadTrainFile(indexes, argv);
    FreeIndexes(indexes);

    return EXIT_SUCCESS;
}
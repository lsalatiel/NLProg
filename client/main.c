#include "libraries.h"

int main(int argc, char** argv) {
    // CheckDataFilesPath(argc);

    argv[1] = "datasets/tiny/train.txt";

    Indexes* indexes = NULL;
    indexes = AllocateIndexes(indexes);
    indexes = ReadTrainFile(indexes, argv);
    indexes = ReadInfo(indexes);
    FreeIndexes(indexes);

    return EXIT_SUCCESS;
}
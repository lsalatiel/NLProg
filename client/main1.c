#include "libraries.h"

int main(int argc, char** argv) {
    // CheckDataFilesPath(argc);

    argv[1] = "datasets/tiny/train.txt";
    argv[2] = "lulu.bin";

    Indexes* indexes = NULL;
    indexes = AllocateIndexes(indexes);
    indexes = ReadTrainFile(indexes, argv);
    indexes = ReadInfo(indexes);
    SaveIndexesInBinary(indexes, argv[2]);
    FreeIndexes(indexes);

    return EXIT_SUCCESS;
}
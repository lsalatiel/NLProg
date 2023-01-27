#include "libraries.h"

int main(int argc, char** argv) {
    CheckDataFilesPath1(argc);

    Indexes* indexes = AllocateIndexes();
    indexes = ReadTrainFile(indexes, argv[1]);
    indexes = ReadInfo(indexes, argv[1]);
    WriteIndexesInBinaryFile(indexes, argv[2]);
    GenerateOutputInfo(indexes, argv[2]);
    FreeIndexes(indexes);

    return EXIT_SUCCESS;
}
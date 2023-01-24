#include "libraries.h"

int main(int argc, char** argv) {
    // CheckDataFilesPath(argc);

    argv[1] = "binary/lulu.bin";
    argv[2] = "10";

    Indexes* indexes = AllocateIndexes();
    indexes = ReadIndexesFromBinaryFile(indexes, argv[1]);

    while (ONLINE) {
        switch (SetUpMainMenu()) {
            case 1:
                SearchAndSortNews(indexes);
                break;
            case 2:
                SortNews(indexes, atoi(argv[2]));
                break;
            case 3:
                GenerateWordRelatory(indexes);
                break;
            case 4:
                GenerateDocumentRelatory(indexes);
                break;
            case 5:
                FreeIndexes(indexes);
                return 0;
        }
    }
}
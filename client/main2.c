#include "libraries.h"

int main(int argc, char** argv) {
    argv[1] = "lulu.bin";

    ClearTerminal();
    Indexes* indexes = NULL;
    indexes = AllocateIndexes();
    indexes = ReadIndexesFromBinaryFile(indexes, argv[1]);

    while (ONLINE) {
        switch (SetUpMainMenu()) {
            case 1:
                SearchAndSortNews(indexes);
                break;
            case 2:

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
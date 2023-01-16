#include "libraries.h"

int main(int argc, char** argv) {
    argv[1] = "lulu.bin";

    Indexes* indexes = NULL;
    indexes = AllocateIndexes();
    indexes = ReadIndexesFromBinaryFile(indexes, argv[1]);

    while (ONLINE) {
        switch (SetUpMainMenu()) {
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:
                FreeIndexes(indexes);
                return 0;
        }
    }
}
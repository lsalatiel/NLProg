#include "libraries.h"

int main(int argc, char **argv) {
    CheckDataFilesPath(argc);

    FILE *file_in = fopen(argv[1], "r"); // path to the train.txt
    FILE *file_out = fopen(argv[2], "wb"); // name of the file that will be stored the information in binary

    return EXIT_SUCCESS;
}
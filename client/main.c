#include "libraries.h"

int main(int argc, char **argv) {
    CheckDataFilesPath(argc);

    FILE *file_in = fopen(argv[1], "r");
    FILE *file_out = fopen(argv[2], "wb");

    return EXIT_SUCCESS;
}
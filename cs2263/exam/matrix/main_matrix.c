#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#define ADD "add"
#define SUB "sub"

int main(int argc, char *argv[]) {
    int expected = 5;
    if (argc != expected) {
        printf("Received %d arguments, expected %d!", argc, expected);
        return EXIT_FAILURE;
    }

    Matrix* one = fromFile(argv[2]);
    if (one == NULL) {
        printf("Failure reading matrix from: %s", argv[2]);
        return EXIT_FAILURE;
    }

    Matrix* two = fromFile(argv[3]);
    if (two == NULL) {
        printf("Failure reading matrix from: %s", argv[3]);
        destruct(one);
        return EXIT_FAILURE;
    }

    char *command = argv[1];
    int status = EXIT_SUCCESS;
    if (strcmp(ADD, command) == 0) {
        if(!add(one, two)) {
            printf("Error during addition :(");
            status = EXIT_FAILURE;
        }
    } else if (strcmp(SUB, command) == 0) {
        if(!sub(one, two)) {
            printf("Error during subtraction :(");
            status = EXIT_FAILURE;
        }
    } else {
        printf("Unrecognized command: %s", command);
        status = EXIT_FAILURE;
    }

    if (status == EXIT_SUCCESS && !toFile(one, argv[4])) {
        printf("Unable to write to  %s", argv[4]);
        status = EXIT_FAILURE;
    }

    destruct(one);
    destruct(two);

    return status;
}

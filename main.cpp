#include <iostream>
#include <cstring>
#include "GraphsMethodsTest.h"

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "test") == 0) {
        graphMethodsTest();
        return 0;
    }

    return 0;
}

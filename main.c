#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "registers.h"
#include "ram.h"


int main(int argc, char* argv[]) {
    if (strcmp(argv[0], "--test")) {
        if (testRegisters() == 1 && testRAM() == 1)
            printf("All tests passed\n\n\n");
        else 
            printf("Test failed\n\n\n");
    }

    initRegisters();
    printRegisters();
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "registers.h"
#include "ram.h"


// Takes a string (should end in .capy but this is not checked) and a pointer to the RAM. It will then check that
// the file exists and exit the program if it does not. Then, it iterates through each section of 16 characters and
// converts them from binary to a `short` number and put it into the RAM.
//
// WARNING: will stop reading data after 2048 instructions without warning message.
void loadProgram(char* filename, short* ram) {
    FILE* filePtr;
    filePtr = fopen(filename, "r");
    if (filePtr == NULL) {
        printf("Could not open file %s\n", filename);
        exit(0);
    }

    char* endPtr;
    int index = 0;
    char buffer[17];
    while (fgets(buffer, 17, filePtr) != NULL && index < 0x0800) {
        ram[index] = strtol(buffer, &endPtr, 2);
        index++;
    }
}


int main(int argc, char* argv[]) {
    if (strcmp(argv[0], "--test")) {
        if (testRegisters() == 1 && testRAM() == 1)
            printf("All tests passed\n\n\n");
        else 
            printf("Test failed\n\n\n");
    }

    initRegisters();
    loadProgram("test.asm", ram);
    printf("%X\n%X\n%X\n", ram[0], ram[1], ram[2]);

    // printRegisters();
}

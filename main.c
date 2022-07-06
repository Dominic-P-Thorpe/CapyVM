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


void interpretRTypeInstr(unsigned short opcode, unsigned short instr, short* registers, short* ram) {
    unsigned short Rd, Rs, Rt;
    Rd = (instr & 0x0F00) >> 8;
    Rs = (instr & 0x00F0) >> 4;
    Rt = (instr & 0x000F);

    switch (opcode) {
        case 1: // ADD
            registers[Rd] = registers[Rs] + registers[Rt];
            break;
        
        case 2: // SUB
            registers[Rd] = registers[Rs] - registers[Rt];
            break;
        
        case 3: // AND
            registers[Rd] = registers[Rs] & registers[Rt];
            break;
        
        case 4: // OR
            registers[Rd] = registers[Rs] | registers[Rt];
            break;
        
        case 5: // XOR
            registers[Rd] = registers[Rs] ^ registers[Rt];
            break;
        
        case 6: // SLL
            registers[Rd] = registers[Rs] << registers[Rt];
            break;
        
        case 7: // SRL
            registers[Rd] = registers[Rs] >> registers[Rt];
            break;
        
        case 11: // LW
            registers[Rd] = ram[registers[Rs]];
            break;
        
        case 12: // SW
            ram[registers[Rd]] = registers[Rs];
            break;
        
        default:
            printf("Invalid operand %d\n", opcode);
            break;
    }
}


void interpretITypeInstr(unsigned short opcode, unsigned short instr, short* registers, short* ram) {
    unsigned short Rd, Rs, imm;
    Rd = (instr & 0x0F00) >> 8;
    Rs = (instr & 0x00F0) >> 4;
    imm = (instr & 0x000F);

    switch (opcode) {
        case 8: // ADDI
            registers[Rd] = registers[Rs] + imm;
            break;
        
        case 9: // ANDI
            registers[Rd] = registers[Rs] & imm;
            break;
        
        case 10: // ORI
            registers[Rd] = registers[Rs] | imm;
            break;
        
        default:
            printf("Invalid operand\n");
            break;
    }
}


void interpretJTypeInstr(unsigned short opcode, unsigned short instr, short* ram, unsigned short* programCounter) {
    unsigned short addr = (instr & 0x0FFF);

    switch (opcode) {        
        case 13: // JMP
            *programCounter = addr;
            break;
        
        case 14: // BEQ
            break;
        
        default:
            printf("Invalid operand\n");
            break;
    }
}


// Iterates through every instruction in RAM and executes it using one of the helper functions.
void runProgram(short* registers, short* ram) {
    unsigned short programCounter = 0;
    unsigned short currentInstruction = 0;
    unsigned short opcode;
    while (programCounter < 4096) {
        currentInstruction = ram[programCounter];

        // HALT
        if (currentInstruction == 0x0000)
            break;
        
        opcode = (currentInstruction & 0xF000) >> 12;
        if ((opcode >= 1 && opcode < 8) || opcode == 11 || opcode == 12)
            interpretRTypeInstr(opcode, currentInstruction, registers, ram);
        else if (opcode < 11)
            interpretITypeInstr(opcode, currentInstruction, registers, ram);
        else if (opcode < 16) 
            interpretJTypeInstr(opcode, currentInstruction, ram, &programCounter);
        else {
            printf("Invalid opcode %d\n", opcode);
            exit(0);
        }

        if (opcode != 14 || opcode != 15)
            programCounter++;
    } 
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Insufficient command-line arguments!\nUSAGE: ./capyVM _filename [--test]\n");
        exit(0);
    }

    if (argc > 2 && strcmp(argv[2], "--test") == 0) {
        if (testRegisters() == 1 && testRAM() == 1)
            printf("All tests passed\n\n\n");
        else 
            printf("Test failed\n\n\n");
    }

    initRegisters();
    loadProgram(argv[1], ram);
    runProgram(registers, ram);

    printRegisters();
}

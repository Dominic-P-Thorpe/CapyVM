#ifndef REGISTERS
#define REGISTERS

#include <stdio.h>
#include <assert.h>


short int registers[16];


void initRegisters() {
    for (int i = 0; i < 16; i++) {
        registers[i] = 0;
    }
}


void printRegisters() {
    for (int i = 0; i < 16; i++) {
        printf("%02d:   %05d\n", i, registers[i]);
    }
}


short getRegister(int reg) {
    if (reg < 0 || reg > 15)
        printf("Invalid register %d!\n", reg);
    
    return registers[reg];
}


void setRegister(int reg, short value) {
    if (reg < 0 || reg > 15)
        printf("Invalid register %d!\n", reg);
    else if (reg == 0) {
        printf("$zero is read-only\n");
        return;
    }
    
    registers[reg] = value;
}


int testRegisters() {
    // testing register initialisation
    initRegisters();
    assert(registers[0] == 0);
    assert(registers[2] == 0);
    assert(registers[10] == 0);
    assert(registers[15] == 0);

    // testing getting and setting registers
    setRegister(1, 20);
    assert(getRegister(1) == 20);
    setRegister(10, 30);
    assert(getRegister(10) == 30);
    setRegister(15, 2);
    assert(getRegister(15) == 2);
    setRegister(0, 20);
    assert(getRegister(0) == 0);
    setRegister(1, -20);
    assert(getRegister(1) == -20);

    return 1;
}


#endif

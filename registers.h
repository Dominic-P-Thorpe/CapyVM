#ifndef REGISTERS
#define REGISTERS


short registers[16];

void initRegisters();
void printRegisters();
short getRegister(int reg);
void setRegister(int reg, short value);
int testRegisters();


#endif

#ifndef RAM
#define RAM


short ram[4096];

void initRAM();
void setRAM(short addr, short data);
short getRAM(short addr);
int testRAM();


#endif

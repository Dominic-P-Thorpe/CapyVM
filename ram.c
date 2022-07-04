#include <assert.h>
#include "ram.h"


void initRAM() {
    for (int i = 0; i < 4096; i++) {
        ram[i] = 0;
    }
}


void setRAM(short addr, short data) {
    if (addr < 0 || addr > 4095) 
        print ("RAM address %d outside of permitted range 0-4096", addr);
    
    ram[addr] = data;
}


short getRAM(short addr) {
    if (addr < 0 || addr > 4095) 
        print ("RAM address %d outside of permitted range 0-4096", addr);
    
    return ram[addr];
}


int testRam() {
    // test inititalising RAM
    initRAM();
    assert(ram[0] == 0);
    assert(ram[4095] == 0);
    assert(ram[2000] == 0);

    // test getting and setting RAM
    setRAM(0, 50);
    setRAM(10, 30);
    setRAM(2000, 20);
    setRAM(4095, 50);
    
    assert(getRAM(0) == 50);
    assert(getRAM(10) == 30);
    assert(getRAM(2000) == 20);
    assert(getRAM(4095) == 50);

    // reset RAM
    initRAM();

    return 1;
}

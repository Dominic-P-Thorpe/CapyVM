# The Capybara Computer VM

This project simulates the hardware of the Capybara Computer: a 16-bit, simplified computer architecture with 16 registers and 16-bit instructions and word sizes. So far, there is no support planned for floating point numbers, however, this may be implemented in the future.

## System Specifications

RAM: HM6116-4 (8Kb as 4096 words of 2b, Hitachi)

ROM: 0 bytes

Clock Speed: 20Hz

ALU: DM74LS181 (Fairchild Semiconductors)

## Assembly Specs

### Instructions

Instructions are formatted in 3 different ways for arithmetic (R-Type), immediate (I-Type), and jump (J-Type) type instructions.

R-type instructions take 3 registers as arguments:
 - *Rd:* The destination register, where the result of the command is stored.
 - *Rs:* The source register, the 1st argument in a command
 - *Rt:* The target register, the 2nd argument in a command

I-type instructions are the same except *Rt* is replaced by *Imm* which is a fixed value hardcoded into the instruction.

A-type instructions take only an argument called *Addr* which is a 12-bit address for a location in memory. The entirety of memory can be addressed.

| Type   | 0-3 | 4-7 | 8-11 | 12-15     |
|--------|-----|-----|------|-----------|
|R-Type: | Op-Code   | Rd   | Rs | Rt   |
|I-Type: | Op-Code   | Rd   | Rs | Imm  |
|J-Type: | Op-code   | Addr (12 bits)   

The instructions are as follows:

| Name | Opcode | Type   | Explanation                |
|------|--------|--------|----------------------------|
| HALT | 0000   | N/A    | Stops program execution    |
| ADD  | 0001   | R-Type | Rd = Rs + Rt               |
| SUB  | 0010   | R-Type | Rd = Rs - Rt               |
| AND  | 0011   | R-Type | Rd = Rs && Rt              |
| OR   | 0100   | R-Type | Rd = Rs || Rt              |
| XOR  | 0101   | R-Type | Rd = Rs XOR Rt             |
| SLL  | 0110   | R-Type | Rd = Rs << Rt              |
| SRL  | 0111   | R-Type | Rd = Rs >> Rt              |
| ADDI | 1000   | I-Type | Rd = Rs + Imm              |
| ANDI | 1001   | I-Type | Rd = Rs && Imm             |
| ORI  | 1010   | I-Type | Rd = Rs || Imm             |
| LW   | 1011   | R-Type | Rd = Value of Addr in RAM  |
| SW   | 1100   | R-Type | Addr in RAM = Rd           |
| JMP  | 1101   | J-Type | PC = Addr                  |
| BEQ  | 1110   | J-Type | PC = Addr if 0 flag is set |


### Registers

There are 16 registers in the system, of which 15 are writeable, and 1 is read-only (*$zero*). 

The *$zero* register will always hold the value of 0. $t0-3 hold temporary values which may be flushed if neccessary, whereas $s0-5 hold global variables in intended usage. 

The global pointer *\$gp* points to where the section for data starts and for program instructions ends. The stack pointer *\$sp* points to the top of the stack which starts off empty at the end of the data memory at 0xFFF. The frame pointer *\$fp* points to the address of the current function frame. The return address register *\$ra* points to the address to return to when the current function is done. The result register *\$r0* holds the result of a function when it is completed.

| No. | Name    | Usage      | Address  |
|-----|---------|------------|----------|
| 00  | $zero   | Constant 0 | 0000     |
| 01  | $t0     | Temp       | 0001     |
| 02  | $t1     | Temp       | 0010     |
| 03  | $t2     | Temp       | 0011     |
| 04  | $t3     | Temp       | 0100     |
| 05  | $s0     | Global     | 0101     |
| 06  | $s1     | Global     | 0110     |
| 07  | $s2     | Global     | 0111     |
| 08  | $s3     | Global     | 1000     |
| 09  | $s4     | Global     | 1001     |
| 10  | $s5     | Global     | 1010     |
| 11  | $gp     | Global Ptr | 1011     |
| 12  | $sp     | Stack Ptr  | 1100     |
| 13  | $fp     | Frame Ptr  | 1101     |
| 14  | $rv     | Return Ptr | 1110     |
| 15  | $r0     | Return Val | 1111     |
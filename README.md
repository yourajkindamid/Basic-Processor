# Standard Computer System 4096 x 17

A customized computer system was based on the basic computer by Mano with numerous architectural improvements.

## Overview of project
The design for the custom computer system is complete, consisting of a 4096 x 17 computer, which provides 4096 addressable memory locations with 17 bits of information for each of those locations. The design of the computer encompasses many subsystems such as memory, registers, bus system, ALU, instruction set, and control unit.

## Key features
- B Register – A secondary operand register is available to facilitate direct register to register operations on the ALU, providing for fewer memory accesses during the execution of many operands.

- Carry Lookahead Adder (CLA) – Has replaced the ripple carry adder from Mano's computer providing for faster multiplication with all carries being computed at the same time.

- Comparator unit – Supports the following four comparison conditions; greater than, less than, equal to, and not equal to, and includes a dedicated register (CPR) for storing results.

- DeMorgan logic expansion unit – Allows extended logic operations to be created (NAND, NOR, XOR, and XNOR) based on DeMorgan's theorems.

- Ring counter – Replaces the existing sequence counter (4 bit) in the control unit with an additional (16) cycles within one count.

- 17 Bit Instruction Format – 1 bit addressing mode | 5 bit opcode | 11 bit address field, will allow for a total of 32 operations and both direct and indirect addressing.

- Dual Bus Topology – There are two buses - data bus (16 bits) and control bus - which eliminates any potential signal contention.

- Interrupt System – The hardware includes an interrupt system, including IEN, FGI, FGO and R

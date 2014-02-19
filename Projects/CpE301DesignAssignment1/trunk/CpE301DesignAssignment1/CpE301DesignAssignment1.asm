/*
 * CpE301DesignAssignment1.asm
 *
 *  Created: 2/19/2014 1:06:01 AM
 *   Author: Ronobir Mookherjee 
 * Description: Simple program to add 20 numbers to a stack, then parse the numbers, applying computer arithmetic alogrithms in the place of available instructions. Must ulitize loops and basic RISC ISA Assembly
 */ 
 .INCLUDE "M328PDEF.INC"; Defines the Memory Map 
 .ORG 0; Beginning Address
 .EQU Loop1 = 6; First loop that pushes 20 numbers to the stack  
 Main: ; Main Body of progam 
 PartA:; As in the product description, must initialize the memory stack using the end of the available memory locations of the device, and then using the stack pointers SPL and SPH for the low and high set of bits of the address, assigned to one register  
 LDI R16, HIGH(RAMEND) 
 OUT SPH, R16 
 LDI R16, LOW(RAMEND) 
 OUT SPL, R16
 LDI R20, 31; initial value being pushed to the stack that is above 30 but below 250 
 LDI R21, 2
 LDI R22, 4
 LDI R23, 8 
 LDI R17, Loop1
 LDI R24, 0; checking total number of increments, initializing second counter 
 INC R24
 L1: PUSH R20; Loop initialized with the first value pushed to the stack 
 ADD R20, R21 
 PUSH R20 
 INC R24
 SUB R20, R22
 PUSH R20
 INC R24 
 ADD R20, R23
 INC R24
 DEC R17 
 BRNE L1 ; Based on the previous statement, once the counter, stored in R17 is complete, 19 numbers have been pushed to the stack with one more left. 
 SUB R20, R23
 PUSH R20
 INC R24 ; Making sure that 20 numbers have been pushed, using this second counter 
 PartB: 

 EndLoop: ; Main Program end 
 sleep
 nop ; breakpoint
 rjmp EndLoop
 
  


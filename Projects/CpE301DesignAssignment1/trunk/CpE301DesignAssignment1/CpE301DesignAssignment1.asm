/*
 * CpE301DesignAssignment1.asm
 *
 *   Author: Ronobir Mookherjee 
 * Description: Simple program to add 20 numbers to a stack, then parse the numbers, applying computer arithmetic alogrithms in the place of available instructions. Must ulitize loops and basic RISC ISA Assembly
 */ 
 .INCLUDE "M328PDEF.INC"; Defines the Memory Map 
 .ORG 0; Beginning Address
 .EQU Loop1 = 4; First loop that pushes 20 numbers to the stack  
 Main: ; Main Body of progam 
 PartA:; As in the product description, must initialize the memory stack using the end of the available memory locations of the device, and then using the stack pointers SPL and SPH for the low and high set of bits of the address, assigned to one register  
 LDI R16, HIGH(RAMEND) ; initiates the stack started at the end of the available memory location
 OUT SPH, R16 ; the MCUs special stack register, with the H denoting the High bit of the address
 LDI R16, LOW(RAMEND) 
 OUT SPL, R16 ; similar to above with the L denoting the low bit 
 LDI R18, 31; initial value being pushed to the stack that is above 30 but below 250 
 LDI R19, Loop1
 CLR R27
 LOOP: ; This loop simply uses the increment and decrement operations to generate new numbers that get pushed to the stack 
 INC R18
 INC R18
 INC R18
 DEC R18
 PUSH R18
 INC R27
 DEC R18
 DEC R18
 INC R18
 PUSH R18
 INC R27
 INC R18
 INC R18
 PUSH R18
 INC R27
 DEC R18
 DEC R18
 DEC R18
 PUSH R18
 INC R27
 INC R18
 INC R18
 INC R18
 INC R18
 INC R18
 INC R18
 INC R18
 PUSH R18
 INC R27
 DEC R19
 BRNE LOOP
 /*LDI R21, 2 ; value used to generate new numbers
 LDI R22, 4 ; above
 LDI R19, 8 ; above 
 LDI R17, Loop1 ; Counter used for main loop in random value generation
 LDI R27, 0; checking total number of increments, initializing second counter 
 INC R27 ; increments the loop everytime any arithmetic action is performed on register 18, which holds the value being pushed to the stack 
 L1: PUSH R18; Loop initialized with the first value pushed to the stack 
 ADD R18, R21 ; Adds 2 to the value in R18, generating a new number
 PUSH R18 ; pushing the new value to the stack
 INC R27 ; increments the arithmetic count register that must equal 20 
 SUB R18, R22 ; subtracts 4 from the value in R18, generating a new value
 PUSH R18 ; push new value to stack 
 INC R27 ; above
 ADD R18, R19 ; adds 8 to R18, generating a new value to be pushed
 INC R27 ;above
 DEC R17 ; decrements the main loop stated above. 
// /*Loop information
 * The loop was initialized with one of the 20 numbers already created, so the loop can consist of 3 parts, running for 6 iterations, creating 18 new numbers, which is even. The final number is made after the loop finishes, which is below 
 *///
// BRNE L1 ; Based on the previous statement, once the counter, stored in R17 is complete, 19 numbers have been pushed to the stack with one more left. 
 //SUB R18, R19
 //PUSH R18
 //INC R27 ; Making sure that 20 numbers have been pushed, using this second counter */
 
 // The second part of the program, designed to parse the stack and find certain criteria, in this case divisibility by a certain quotient. These values must then be placed in a certain register
 PartB: 
 CLR R20 ; Clearing required register
 CLR R21; Clearing required register, both are used for storing the sum of numbers divisble by 3 in the stack 
 CLR R23; Cleared and initialized register used to store the sum of numbers divisible by 5 in the stack 
 CLR R18; clearing register for use
 CLR R19; for checking 3
 CLR R25; for checking for 5
 LDI R17, 3; REGISTER HOLDING 3
 LDI R26, 5; REGISTER HOLDING 5
 CLR R22
 L2: POP R18
 MOV R19, R18
 MOV R25, R18 
 SUBLOOP3: // This loop proves divisibility by 3, by using an algorithm based on subtracting. If it is greater than the value 3, keep subtracting, if it is 0, it is divisible, if carry is set, then 
 SUB R19, R17
 BRNE SUBLOOP3
 BRMI SUBLOOP5
 //END LOOP
 Addition: ADD R21, R18
 SUBLOOP5:
 SUB R25, R26
 BRNE SUBLOOP5
 BRMI EOL
 //END LOOP
 Addition2: ADD R23, R18
 EOL:
 DEC R27
 BRNE L2
 EndLoop: ; Main Program end 
 sleep
 nop ; breakpoint
 rjmp EndLoop
 
  


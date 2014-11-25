#include "spimcore.h"

/* ALU */
/* 10 Points */

/* This function represents the ALU (Arithmetic Logic Unit), which performs arithmetic
 * calculations such as: add, substract, less than, logical and, logical or, shift left,
 * and logical not.
 */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero) {
	
	switch (ALUControl) {
		case '0': 							// Z = A + B 
			*ALUresult = A + B;
			break;
		case '1': 							// Z = A - B 
			*ALUresult = A - B;
			break;
		case '2': 							// if A < B, Z = 1; otherwise, Z = 0
			*ALUresult = (A < B) ? 1 : 0;
			break;
		case '3': 							// if A < B, Z = 1; otherwise, Z = 0 (A and B are unsigned integers)
			*ALUresult = ((int)A < (int)B) ? 1 : 0;
			break;
		case '4': 							// Z = A AND B 
			*ALUresult = A & B;
			break;
		case '5': 							// Z = A OR B
			*ALUresult = A | B;
			break;
		case '6':							// shift left B by 16 bits
			*ALUresult = B << 16;
			break;
		case '7':							// Z = NOT A
			*ALUresult = ~A;
			break;
			
	}
	
	*Zero = (*ALUresult == 0) ? '1': '0';

	return;
}

/* instruction fetch */
/* 10 Points */

/* This function fetchs the instruction from memory based on where the PC
 * counter is.  It also, checks if the PC counter is within the range of
 * memory and if it is word aligned.
 */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
	// check if PC is within the memory OR if the address is not word aligned 
	if (PC%4 != 0 || (PC >> 2) >= 65536) {
		return 1;
	}

	// fetch instruction 
	*instruction = Mem[PC >> 2]; 
	return 0;
}


/* instruction partition */
/* 10 Points */

/* This functions takes in the instruction (32 bits) and grabs the relevant piece of the instruction 
 * to the respective code, by a mixture of either shifting or mask or both.  
   op: [31-26] 
   r1: [25-21] 
   r2: [20-16]
   r3: [15-11]
   funct: [5-0]
   offset: [15-0]
   jsec: [25-0]
 */ 
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec) {

	*op = instruction >> 26;
	*r1 = instruction >> 21 & 0x1F;
	*r2 = instruction >> 16 & 0x1F;
	*r3 = instruction >> 11 & 0x1F;
	*funct = instruction & 0x3F;
	*offset = instruction & 0xFFFF;
	*jsec = instruction & 0x3FFFFFF;

	return;
}



/* instruction decode */
/* 15 Points */

/* This function takes in the op code of the instruction (bits [31-26]) and 
 * sets the disables (0), enables (1), or don't care (2) the control signals
 * The only exception is 'ALUOp' it can be assign a value 0-7 (based on the
 * table provided).
 */
int instruction_decode(unsigned op,struct_controls *controls) {

	switch (op) {
		case 0:							// r type 
			controls->MemRead = '0';
			controls->MemWrite = '0';
			controls->RegWrite = '1';
			controls->RegDst = '1';
			controls->Jump = '0';
			controls->Branch = '0';
			controls->MemtoReg = '0';
			controls->ALUSrc = '0';
			controls->ALUOp = '7';
			break;
	
		case 2:							// jump
			controls->MemRead = '0';
			controls->MemWrite = '0';
			controls->RegWrite = '0';
			controls->RegDst = '2';
			controls->Jump = '1';
			controls->Branch = '0';
			controls->MemtoReg = '0';
			controls->ALUSrc = '1';
			controls->ALUOp = '0';
			break;

		case 4:							// beq
			controls->MemRead = '0';
			controls->MemWrite = '0';
			controls->RegWrite = '0';
			controls->RegDst = '2';
			controls->Jump = '0';
			controls->Branch = '1';
			controls->MemtoReg = '0';
			controls->ALUSrc = '0';
			controls->ALUOp = '1';
			break;

		case 8:							// addi	
			controls->MemRead = '0';
			controls->MemWrite = '0';
			controls->RegWrite = '1';
			controls->RegDst = '0';
			controls->Jump = '0';
			controls->Branch = '0';
			controls->MemtoReg = '0';
			controls->ALUSrc = '1';
			controls->ALUOp = '0';
			break;
		
		case 10:						// slti
			controls->MemRead = '0';
			controls->MemWrite = '0';
			controls->RegWrite = '1';
			controls->RegDst = '0';
			controls->Jump = '0';
			controls->Branch = '0';
			controls->MemtoReg = '0';
			controls->ALUSrc = '1';
			controls->ALUOp = '2';
			break;
		
		case 11:						// sltiu
			controls->MemRead = '0';
			controls->MemWrite = '0';
			controls->RegWrite = '1';
			controls->RegDst = '0';
			controls->Jump = '0';
			controls->Branch = '2';
			controls->MemtoReg = '0';
			controls->ALUSrc = '1';
			controls->ALUOp = '3';
			break;
		
		case 15:						// lui
			controls->MemRead = '0';
			controls->MemWrite = '0';
			controls->RegWrite = '1';
			controls->RegDst = '0';
			controls->Jump = '0';
			controls->Branch = '0';
			controls->MemtoReg = '0';
			controls->ALUSrc = '1';
			controls->ALUOp = '6';
			break;
		
		case 35: 						// lw
			controls->MemRead = '1';
			controls->MemWrite = '0';
			controls->RegWrite = '1';
			controls->RegDst = '0';
			controls->Jump = '0';
			controls->Branch = '0';
			controls->MemtoReg = '1';
			controls->ALUSrc = '1';
			controls->ALUOp = '0';   
			break;
		
		case 43: 						// sw
			controls->MemRead = '0';
			controls->MemWrite = '1';
			controls->RegWrite = '0';
			controls->RegDst = '2';
			controls->Jump = '0';
			controls->Branch = '0';
			controls->MemtoReg = '0';
			controls->ALUSrc = '1';
			controls->ALUOp = '0';
			break;

		default:						// halt condition
			return 1;

	} // end switch 

	return 0;

}

/* Read Register */
/* 5 Points */

/* This function takes in two pieces of the current instruction (i.e. r1, r2) and writes
 * the values from the registers indicated by 'r1' and 'r2' to the two data variables. 
 */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2) {

	*data1 = Reg[r1];
	*data2 = Reg[r2];

	return;
}


/* Sign Extend */
/* 10 Points */

/* This funciton looks at the MSB of the offset.  If the bit is 0, the number is positive otherwise
 * if the bit is 1, the number is negative.  By shift right, we can check to see what the MSB of the 
 * offset is because it represents 16-bit number (i.e. bits [15-0] in the instruction).  If it is zero
 * we leave the offset alone and assign it to the extended_value otherwise, if negative, extend the 
 * offset by 16-bit makes the 'extended_value' a 32-bit number.  
 */
void sign_extend(unsigned offset,unsigned *extended_value) {

	*extended_value = (offset >> 15) == 0 ? offset : (offset | 0xFFFF0000);

	return;
}

/* ALU operations */
/* 10 Points */

// ******************************************************************************************************************
// ******************************************************************************************************************
// ******************************************************************************************************************
// ******************************************************************************************************************
// WORK ON THIS ONE WORK ON THIS ONE WORK ON THIS ONE WORK ON THIS ONE WORK ON THIS ONE WORK ON THIS ONE WORK ON THIS ONE 
// ******************************************************************************************************************
// ******************************************************************************************************************
// ******************************************************************************************************************
// ******************************************************************************************************************

/*** ALU operations
*		In the ALU operations stage, you look at the ALUSrc control signal to see whether or not you're going to need to use r2 in your ALU 
*		or if you're going to use the extended offset. With an ALUSrc of 0, you use register 2 and the ALU operation is dictated by the funct 
*		value (or in the case of branching on equal, if the ALUOp control signal is 1). With an ALUSrc of 1, you use the extended offset in your
*		ALU operation and you use your ALUOp control signal to determine the operation. 
***/
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero) {

	// R-Type
	if (ALUSrc == '0') { 	

		// Add
		if(funct == 32)  {
			ALU(data1, data2, '0', ALUresult, Zero); 
			return 0; 
		}

		// Subtract
		else if(funct == 34) {
			ALU(data1, data2, '1', ALUresult, Zero); 
			return 0;
		}
		
		// AND
		else if(funct == 36) {
			ALU(data1, data2, '4', ALUresult, Zero); 
			return 0;
		}

		// OR
		else if(funct == 37) {
			ALU(data1, data2, '5', ALUresult, Zero); 
			return 0;
		}

		// Set Less (Signed) 
		else if(funct == 42) {
			ALU(data1, data2, '2', ALUresult, Zero); 
			return 0; 
		}

		// Set Less (Unsigned) 
		else if(funct == 43) {
			ALU(data1, data2, '3', ALUresult, Zero); 
			return 0;
		}

		// Beq
		else if(ALUOp == '1') {
			ALU(data1, data2, '1', ALUresult, Zero);
			return 0;
		}

		// halt condition
		return 1;
	}

	// I-Type && Branching
	else if (ALUSrc == '1') {

		// addi && sw && lw
		if(ALUOp == '0') {
			ALU(data1, extended_value, ALUOp, ALUresult, Zero); 
			return 0;
		} 

		// slti 
		else if(ALUOp == '2') {
			ALU(data1, extended_value, ALUOp, ALUresult, Zero); 
			return 0;
		}

	
		// sltiu
		else if(ALUOp == '3') {
			ALU(data1, extended_value, ALUOp, ALUresult, Zero); 
			return 0;
		}

		// lui
		else if(ALUOp == '6') {
			ALU(data1, extended_value, ALUOp, ALUresult, Zero); 
			return 0;
		}
	
		// halt condition
		return 1;
	}
	
	// halt condition
	return 1;
}

/* Read / Write Memory */
/* 10 Points */
/*** Read or Write Memory
*		In the memory read write stage, you check your MemWrite and MemRead control signals to determine if you're
*		going to be reading or writing to memory. If your're going to be reading or writing, then you have to check
*		your program counter to make sure that it's word-aligned. If it's not, then the program will halt, because 
*		writing to an un-aligned address will completely screw up your memory (or your registers). When you write to 
*		memory, you write a register value to the address obtained from the ALU adding together an offset with a register 
		value and when you read from memory, you read from that address into a register. 
***/
int rw_memory(unsigned ALUresult,unsigned data1,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
	if ((ALUresult % 4) != 0 && (MemWrite == '1' || MemRead == '1'))
		return 1;
	if (ALUresult > 65536 && (MemWrite == '1' || MemRead == '1'))
		return 1;
		
	ALUresult = ALUresult >> 2;
	if (MemWrite == '1')
	{
		Mem[ALUresult] = data1;
	}
	if (MemRead == '1')
	{
		*memdata = Mem[ALUresult];
	}
	return 0;
}


/* Write Register */
/* 10 Points */
/*** Write register
*		In the register write stage, you need to check your RegWrite control signal to see if you're allowed to write to a register.
*		If you are, then you need to check whether or not you're going to be writing from memory or from the ALU result (MemtoReg control
*		signal determines this). If your RegDst control signal is 0, you're going to be writing to r2 and if it's 1, you're going to be writing
*		to r3. 
***/
/* This function first checks to if you RegWrite is even enabled, because if not we can by pass everything a return nothing w/o doing
 * and work.  If RegWrite is enabled MemtoReg controls whether the program is writing from memory of the ALU's results.  If MemtoReg is
 *
 */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg) {

	// only write if RegWrite is enabled otherwise return w/o doing anything
	if (RegWrite == '1') {

		if (MemtoReg == '0' && RegDst == '0') {
			Reg[r2] = ALUresult; 
		}

		else if (MemtoReg == '0' && RegDst == '1')	{ 
			Reg[r3] = ALUresult; 
		}

		else if (MemtoReg == '1' && RegDst == '0') {
			Reg[r2] = memdata; 
		}

		else if (MemtoReg == '1' && RegDst == '1') { 
			Reg[r3] = memdata; 
		}
	}

	return;
}

/* PC update */
/* 10 Points */

/* This function updates the program counter to point to the next instruction.  It starts by incrementing the PC 
 * by 4 to point to the very next instruction.  It also, handles when the a jump occurs as wells as a branch.  
 * When a branch (beq) occurs the PC counter is updated by the offset.  And when a Jump occurs the PC is masked
 * and then added (bitwise OR) with the jsec.
 */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC) {
	
	// increment the program counter --> to the next instruction is memory	
	*PC += 4;

	// add the extended value to the program count when both Branch (beq) and Zero are 1	
	if (Branch == '1' && Zero == '1') {
		*PC += extended_value << 2;
	}	
	
	// 0xF0000000 mask --> 1111 1000 0000 0000 0000 0000 0000 0000 (32-bit binary number) 
	// here we are only interested in the first 4 MSB of the Program Counter
	// and then we bitwise or the masked PC with the jsec shifted left by 2 
	if (Jump == '1') {
		*PC = (*PC & 0xF0000000) | (jsec << 2);	
	}

	return;
}

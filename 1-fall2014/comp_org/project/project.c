/*
 * Author: Ben Feistmann
 *
 */

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

/* This function takes in the ALUSrc and depending on whether it is 1 or 0 decides whether use data2 versus the extended value in the ALU().
 * Also, the ALUSrc dictated whether it is and R-type instruction or I-type instruction. 
 */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero) {

	// R-type --> use data2
	if (ALUSrc == '0') { 	
		
		// Add --> add z,a,b; 3 operands; overflow detected
		if(funct == 32)  {
			ALU(data1, data2, '0', ALUresult, Zero); 
			return 0; 
		}

		// Subtract --> sub z,a,b; 3 operands; overflow detected
		else if(funct == 34) {
			ALU(data1, data2, '1', ALUresult, Zero); 
			return 0;
		}
		
		// AND --> and z,a,b; 3 operands; logical AND
		else if(funct == 36) {
			ALU(data1, data2, '4', ALUresult, Zero); 
			return 0;
		}

		// OR --> or z,a,b; 3 operands; logical OR
		else if(funct == 37) {
			ALU(data1, data2, '5', ALUresult, Zero); 
			return 0;
		}

		// Set Less (Signed) --> slt z,a,b; compare less than; two's compliment
		else if(funct == 42) {
			ALU(data1, data2, '2', ALUresult, Zero); 
			return 0; 
		}

		// Set Less (Unsigned) --> sltu z,a,b; compare less than; natural number
		else if(funct == 43) {
			ALU(data1, data2, '3', ALUresult, Zero); 
			return 0;
		}

		// Branch on Equal --> beq z,a,b; equal test; PC relative branch
		else if(ALUOp == '1') {
			ALU(data1, data2, '1', ALUresult, Zero);
			return 0;
		}
		
		// halt condition
		else {	
			return 1;
		}
	}

	// I-type && Branching --> use the extended value
	else if (ALUSrc == '1') {

        // addi z,a,i; + constant; overflow detected
        // sw z,i(a); word from register to memory
        // lw z,i(a); word from memory to register
		if(ALUOp == '0') {
			ALU(data1, extended_value, ALUOp, ALUresult, Zero); 
			return 0;
		} 

		// slti --> slti z,a,i; compare<constant; two's compliment
		else if(ALUOp == '2') {
			ALU(data1, extended_value, ALUOp, ALUresult, Zero); 
			return 0;
		}

	
		// sltiu --> sltiu z,a,i; compare<constant; natural number
		else if(ALUOp == '3') {
			ALU(data1, extended_value, ALUOp, ALUresult, Zero); 
			return 0;
		}

		// lui --> lui z,i; loads constant in upper 16 bits
		else if(ALUOp == '6') {
			ALU(data1, extended_value, ALUOp, ALUresult, Zero); 
			return 0;
		}
	
		// halt condition
		else {
			return 1;
		}
	}
	
	// halt condition
	else {
		return 1;
	}
}

/* Read / Write Memory */
/* 10 Points */

/* This function takes in MemWrite and MemRead to decide whether you are going to be writing or reading to memory.
 * Also, we are checking the PC to verify if it is word aligned.  If it's not aligned, then a halt condition is 
 * met and we return 1 right away without doing anything else in the function.  Before reading or writing to memory
 * we have to shift the ALUresult right by 2 (i.e. dividing by 2^2 = 4).  Then, depending of the value of 
 * MemWrite and MemRead we assign the proper to values to Mem[] and memdata respectively.
 */
int rw_memory(unsigned ALUresult,unsigned data1,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem) {

	// check if Memory Address is word-aligned && if Memory is to be written or read
	if ((ALUresult % 4) != 0 && (MemWrite == '1' || MemRead == '1')) {
		return 1;
	}

	// check if Memory address is within the Memory address limit && if Memory is to be written or read
	if (ALUresult > 65536 && (MemWrite == '1' || MemRead == '1')) {
		return 1;
	}

	// shift right 2 places to divide by 4 for word-aligned Mem[] address	
	ALUresult = ALUresult >> 2;

	// check if memory is to be written 
	if (MemWrite == '1') { 
		Mem[ALUresult] = data1; 			// write data1 to the memory address desired
	}

	// check if memory is to be read
	if (MemRead == '1') { 
		*memdata = Mem[ALUresult]; 			// read memory at desired address into temporary register memdata
	}

	return 0;
}


/* Write Register */
/* 10 Points */

/* This function first checks to if you RegWrite is even enabled, because if not we can by pass everything a return nothing w/o doing
 * and work.  If RegWrite is enabled MemtoReg controls whether the program is writing from memory of the ALU's results.  If MemtoReg is
 * 0 we arr writing the ALUresult in Reg[], but if it is MemReg is 1 we are writing memdata to Reg[].   
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

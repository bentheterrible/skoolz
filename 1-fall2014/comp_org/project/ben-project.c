#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
	switch (ALUControl) {

		case '000':
			ALUresult = A + B;
			Zero = (ALUresult == 0) ? 1 : 0; 
			break;
		case '001':
			ALUresult = A - B;
			Zero = (ALUresult == 0) ? 1 : 0; 
			break;
		case '010':
			ALUresult = (A < B) ? 1 : 0;
			Zero = (ALUresult == 0) ? 1 : 0; 
			break;
		case '011':
			ALUresult = (A < B) ? 1 : 0;		// unsigned ?
			Zero = (ALUresult == 0) ? 1 : 0; 
			break;
		case '100':
			ALUresult = A & B;
			Zero = (ALUresult == 0) ? 1 : 0; 
			break;
		case '101':
			ALUresult = A | B;
			Zero = (ALUresult == 0) ? 1 : 0; 
			break;
		case '110':
			ALUresult = B << 16;
			Zero = (ALUresult == 0) ? 1 : 0; 
			break;
		case '111':
			ALUresult = ~A;
			Zero = (ALUresult == 0) ? 1 : 0; 
			break;
	}
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{

	// Fetch the instruction 
	instruction = Mem[PC];
	
	// Check for the Halt Conditions
	//......	
		
}

void reverse(int *arr, int len) {

	// Declare Variables
	int i, j;
	int temp[len];	

	// Copy array into a temp_array[]
	for (i = 0; i < len; i++) {
		temp[i] = arr[i];
	}
	
	// Place values of temp[] -> arr[] in reverse order	
	for (i = 0, j = len-1; i < len; i++) {
		arr[i] = temp[j--];
	}	
	
	// Go back to where you came from!
	return;	
}

/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
	int i, j, bin[32];

	// Convert the instruction (hex) to a binary number (i.e. bin[32])	
	for (i = 0; i < 32; i++) {
		bin[i] = instruction & 1;
		instruction >>= 1;
	}
	
	/* Break up the binary number and
	 * assign proper binary code to 
	 * repective instruction piece 
	 * (i.e. op, r1, r2, ... , jsec) */

	// op code
	j = 31;	
	for (i = 6; i >= 0; i--) {
		op[i] = bin[j--];
	}		

	// r1 code 
	for (i = 4; i >= 0; i--) {
		r1[i] = bin[j--];
	}	

	// r2 code 
	for (i = 4; i >= 0; i--) {
		r2[i] = bin[j--];
	}

	// r3 code 
	for (i = 4; i >= 0; i--) {
		r3[i] = bin[j--];
	}
	
	// funct code
	for (i = 5; i >= 0; i--) {
		funct[i] = bin[j--];
	}
	
	// offset code
	j = 15;
	for (i = j; i >= 0; i--) {
		offset[i] = bin[j--];
	}

	// jsec code 
	j = 25;
	for (i = j; i >= 0; i--) {
		jsec[i] = bin[j--];
	}
	
	return;
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
	
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

#ifndef __TYPES__
#define __TYPES__

#include "Constants.h"

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <stack>

/**
* Supported token types.
*/
enum TokenType
{
	//
	T_AND,
	T_ANDI,
	T_LB,
	//
	T_NO_TYPE,

	T_ID,			// abcd...
	T_M_ID,			// m123...
	T_R_ID,			// r123...
	T_NUM,			// 123...
	T_WHITE_SPACE,

	// reserved words
	T_MEM,			// _mem
	T_REG,			// _reg
	T_FUNC,			// _func
	T_ADD,			// add
	T_ADDI,			// addi
	T_SUB,			// sub
	T_LA,			// la
	T_LI,			// li
	T_LW,			// lw
	T_SW,			// sw
	T_BLTZ,			// bltz
	T_B,			// b
	T_NOP,			// nop

	// operators
	T_COMMA,		//,
	T_L_PARENT,		//(
	T_R_PARENT,		//)
	T_COL,			//:
	T_SEMI_COL,		//;

	// utility
	T_COMMENT,
	T_END_OF_FILE,
	T_ERROR,
};


/**
 * Instruction type.
 */
enum InstructionType
{
	I_NO_TYPE = 0,
	I_ADD,//1
	I_ADDI,//2
	I_SUB,//3
	I_LA,//4
	I_LI,//5
	I_LW,//6
	I_SW,//7
	I_BLTZ,//8
	I_B,//9
	I_NOP,//10
	I_AND,
	I_ANDI,
	I_LB
};

/**
 * Reg names.
 */
enum Regs
{
	no_assign = 0,
	t0=1,//1
	t1=2,//2
	t2=3,//3
	t3=4//4
	//5
};

#endif

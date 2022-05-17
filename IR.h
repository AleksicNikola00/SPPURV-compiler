#ifndef __IR__
#define __IR__


#include "Types.h"
#include <stack>
#include <vector>

/**
 * This class represents one variable from program code.
 */


class Variable
{
public:
	enum VariableType
	{
		MEM_VAR,
		REG_VAR,
		NO_TYPE
	};

	Variable() : m_type(NO_TYPE), m_name(""), m_position(-1), m_assignment(no_assign) {}
	Variable(std::string name, int pos) : m_type(NO_TYPE), m_name(name), m_position(pos), m_assignment(no_assign) {}
	Variable(std::string name, int pos,double vr) : m_type(NO_TYPE), m_name(name), m_position(pos), m_assignment(no_assign),m_vrednost(vr) {}
	std::string getName() {
		return m_name;
	}
	int getPosition() {
		return m_position;
	}
	Regs& getAssignment() {
		return m_assignment;
	}
	void setAssignment(Regs r) {
		m_assignment = r;
	}
	double getVrednost() {
		return m_vrednost;
	}
private:
	double m_vrednost;
	VariableType m_type;
	std::string m_name;
	int m_position;
	Regs m_assignment;

	
};


/**
 * This type represents list of variables from program code.
 */
typedef std::list<Variable*> Variables;
typedef Variables::iterator varIt;


/**
 * This class represents one instruction in program code.
 */

class Instruction
{
public:
	Instruction () : m_position(0), m_type(I_NO_TYPE) {}
	Instruction (int pos, InstructionType type, Variables& dst, Variables& src) :
		m_position(pos), m_type(type), m_dst(dst), m_src(src) {}
	Instruction(int pos, InstructionType type, Variables& dst, Variables& src,double i) :
		m_position(pos), m_type(type), m_dst(dst), m_src(src),m_imm(i) {}

	InstructionType getInstructionType() {
		return m_type;
	}
	int getPosition() {
		return m_position;
	}
	double getImm() {
		return m_imm;
	}
	void pushSucc(Instruction* i) {
		m_succ.push_back(i);
	}
	void pushPred(Instruction* i) {
		m_pred.push_back(i);
	}
	void setImeLabele(std::string x) {
		m_imeLabele = x;
	}
	std::string getImeLabele() {
		return m_imeLabele;
	}
	Variables& getDst() {
		return m_dst;
	}
	Variables& getSrc() {
		return m_src;
	}
	std::list<Instruction*>& getSucc() {
		return m_succ;
	}
	std::list<Instruction*>& getPred() {
		return m_pred;
	}
	Variables& getIn() {
		return m_in;
	}
	Variables& getOut() {
		return m_out;
	}
	std::string getImeMemorijskePromenjive() {
		return m_imeMemorijskePromenjive;
	}
	void setImeMemorijskePromenjive(std::string i) {
		m_imeMemorijskePromenjive = i;
	}
	void setOffset(double x) {
		m_offset = x;
	}
	double getOffset() {
		return m_offset;
	}

	
	
private:
	std::string m_imeLabele;//u slucaju b i blzt
	std::string m_imeMemorijskePromenjive;
	double m_imm;//u slucaju addi npr
	double m_offset;
	int m_position;
	InstructionType m_type;
	
	Variables m_dst;
	Variables m_src;

	Variables m_use;//isto sto i src
	Variables m_def;//isto sto i dst
	Variables m_in;
	Variables m_out;
	std::list<Instruction*> m_succ;
	std::list<Instruction*> m_pred;
};


//
struct InterferenceGraphStruct
{
	Variables* variables;	///< all variables from instructions
	int** values;			///< matrix value
	int size;				///< size of square matrix
};

struct Labela
{
	std::string ime;
	int gdeSkociti;
	Labela(std::string i, int x):ime(i),gdeSkociti(x) {}
};

struct Function {
	std::string ime;
	Function(std::string x):ime(x){}
};
typedef std::list<Function*> Functions;
typedef Functions::iterator funcIt;

typedef std::list<Labela*> Labels;
typedef Labels::iterator labIt;
/**
 * This type represents list of instructions from program code.
 */
typedef std::list<Instruction*> Instructions;
typedef Instructions::iterator instIt;
typedef Instructions::reverse_iterator instRit;

typedef std::stack<Variable*> Stack;

#endif

#include "SyntaxAnalysis.h"

#include <iostream>
#include <iomanip>



using namespace std;

SyntaxAnalysis::SyntaxAnalysis(LexicalAnalysis& lex)
	: m_lexicalAnalysis(lex), m_errorFound(false), m_tokenIterator(m_lexicalAnalysis.getTokenList().begin())
{
}


bool SyntaxAnalysis::Do()
{
	m_currentToken = getNextToken();

	Q();

	return !m_errorFound;
}


void SyntaxAnalysis::printSyntaxError(Token token)
{
	cout << "Syntax error! Token: " << token.getValue() << " unexpected" << endl;
}


void SyntaxAnalysis::printTokenInfo(Token token)
{
	token.printTokenInfo();
}


void SyntaxAnalysis::eat(TokenType t)
{
	if (m_errorFound == false)
	{
		if (m_currentToken.getType() == T_END_OF_FILE)
			return;

		if (m_currentToken.getType() == t)
		{	
			m_currentToken = getNextToken();
			//currentToken.printTokenInfo();

		}
		else
		{
			m_currentToken.printTokenInfo();
			printSyntaxError(m_currentToken);
			m_errorFound = true;
		}
	}
}


Token SyntaxAnalysis::getNextToken()
{
	if (m_tokenIterator == m_lexicalAnalysis.getTokenList().end())
		throw runtime_error("End of input file reached");
	return *m_tokenIterator++;
}


void SyntaxAnalysis::Q()
{
	if (m_errorFound)
		return;

	S();

	eat(T_SEMI_COL);

	L();
	
}


void SyntaxAnalysis::S()
{
	if (m_errorFound)
		return;
	
	switch (m_currentToken.getType())
	{
	case T_MEM:
		eat(T_MEM);
		eat(T_M_ID);
		eat(T_NUM);
		break;
	case T_REG:
		eat(T_REG);
		eat(T_R_ID);
		break;
	case T_FUNC:
		eat(T_FUNC);
		eat(T_ID);
		break;
	case T_ID:
		eat(T_ID);
		eat(T_COL);
		E();
		break;
	default:
		E();
		break;
	}

}


void SyntaxAnalysis::L()
{
	if (m_errorFound)
		return;

	if (m_currentToken.getType() == T_END_OF_FILE) 
	{
		eat(T_END_OF_FILE);
	}
	else 
	{
		Q();
	}
}


void SyntaxAnalysis::E()
{
	if (m_errorFound)
		return;

	switch (m_currentToken.getType())
	{
		case T_LB:
			eat(T_LB);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_NUM);
			eat(T_L_PARENT);
			eat(T_R_ID);
			eat(T_R_PARENT);
			break;
		case T_ANDI:
			eat(T_ANDI);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_NUM);
			break;
		case T_AND:
			eat(T_AND);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_R_ID);
			break;
		case T_ADD:
			eat(T_ADD);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_R_ID);
			break;
		case T_ADDI:
			eat(T_ADDI);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_NUM);
			break;
		case T_SUB:
			eat(T_SUB);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_R_ID);
			break;
		case T_LA:
			eat(T_LA);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_M_ID);
			break;
		case T_LW:
			eat(T_LW);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_NUM);
			eat(T_L_PARENT);
			eat(T_R_ID);
			eat(T_R_PARENT);
			break;
		case T_LI:
			eat(T_LI);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_NUM);
			break;
		case T_SW:
			eat(T_SW);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_NUM);
			eat(T_L_PARENT);
			eat(T_R_ID);
			eat(T_R_PARENT);
			break;
		case T_B:
			eat(T_B);
			eat(T_ID);
			break;
		case T_BLTZ:
			eat(T_BLTZ);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_ID);
			break;
		case T_NOP:
			eat(T_NOP);
			break;
		default:
			cout << "GRESKA: " << endl;
			m_currentToken.printTokenInfo();
			m_errorFound = true;
			break;
	}
}






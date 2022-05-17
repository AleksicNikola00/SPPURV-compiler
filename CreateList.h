#pragma once
#include "LexicalAnalysis.h"
#include "IR.h"

class CreateList{
public:
	CreateList(LexicalAnalysis& lex);
	void doList(Instructions& listaInstrukcija,Variables& listaRegistarskihPromenjivih, Variables& listaMemorijskihPromenjivih,Labels& labele,Functions& funkcije);
	void deleteList(Instructions& listaInstrukcija, Variables& listaRegistarskihPromenjivih, Variables& listaMemorijskihPromenjivih, Labels& labele, Functions& funkcije);
	static bool compareStrings(std::string str1, std::string str2);
	void povecajIterator(int x);
private:

	int m_brInstrukcije;
	int m_brRegistarskihPromenjivih;
	int m_brMemorijskihPromenjivih;
	bool m_postojiUListi;

	void printTokenInfo(Token token);

	LexicalAnalysis& m_lexicalAnalysis;

	TokenList::iterator m_tokenIterator;

	Token m_currentToken;

	Instruction* m_trenutnaInstrukcija;



	
};
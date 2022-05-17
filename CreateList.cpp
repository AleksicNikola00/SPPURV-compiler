#include "CreateList.h"

#include <iostream>
#include <string>
#include<string.h>


using namespace std;





CreateList::CreateList(LexicalAnalysis& lex)
	: m_lexicalAnalysis(lex), m_tokenIterator(m_lexicalAnalysis.getTokenList().begin()), m_brInstrukcije(0), m_brRegistarskihPromenjivih(0), m_brMemorijskihPromenjivih(0)
{
}

void CreateList::povecajIterator(int x) {
	for (int i = 0; i < x; i++) 
		++m_tokenIterator;
}

bool CreateList::compareStrings(std::string str1, std::string str2) {
	if (strcmp(str1.c_str(), str2.c_str()) == 0)
		return true;

	return false;
}

void CreateList::printTokenInfo(Token token)
{
	token.printTokenInfo();
}



void CreateList::doList(Instructions& listaInstrukcija, Variables& listaRegistarskihPromenjivih,Variables& listaMemorijskihPromenjivih,Labels& labele,Functions& funkcije) {
	Instruction* instrukcija;
	Variable* v;
	Variables dst;
	Variables src;
	Function* f;
	Labela* l;
	double vrednost;
	bool postoji;
	bool postojiMain = false;

	while (m_tokenIterator != m_lexicalAnalysis.getTokenList().end()) 
	{
		switch ((*m_tokenIterator).getType())
		{
		case T_LB:
			postoji = false;
			++m_tokenIterator;
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++) 
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName()))
				{
					postoji = true;
					dst.push_front((*it1));
					break;
				}
			}
			if(!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");

			postoji = false;
			povecajIterator(2);
			vrednost = atof((*m_tokenIterator).getValue().c_str());//offset
			povecajIterator(2);
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++) 
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName())) 
				{
					postoji = true;
					src.push_front((*it1));
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");

			instrukcija = new Instruction(m_brInstrukcije, I_LB, dst, src);
			instrukcija->setOffset(vrednost);
			listaInstrukcija.push_back(instrukcija);
			m_brInstrukcije++;
			dst.clear();
			src.clear();
			break;
		case T_AND:
			++m_tokenIterator;
			postoji = false;
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++)
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName())) 
				{
					postoji = true;
					dst.push_front((*it1));
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");
			postoji = false;
			povecajIterator(2);
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++) 
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName()))
				{
					postoji = true;
					src.push_front((*it1));
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");
			postoji = false;
			povecajIterator(2);
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++)
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName()))
				{
					src.push_front((*it1));
					postoji = true;
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");

			instrukcija = new Instruction(m_brInstrukcije, I_AND, dst, src);
			listaInstrukcija.push_back(instrukcija);
			m_brInstrukcije++;
			dst.clear();
			src.clear();
			break;
		case T_ANDI:
			++m_tokenIterator;
			postoji = false;
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++)
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName()))
				{
					postoji = true;
					dst.push_front((*it1));
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");
			postoji = false;
			povecajIterator(2);
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++)
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName())) 
				{
					postoji = true;
					src.push_front((*it1));
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");

			povecajIterator(2);
			vrednost = atof((*m_tokenIterator).getValue().c_str());//imm
			instrukcija = new Instruction(m_brInstrukcije, I_ANDI, dst, src, vrednost);
			listaInstrukcija.push_back(instrukcija);
			m_brInstrukcije++;
			dst.clear();
			src.clear();
			break;
		case T_FUNC:
			++m_tokenIterator;
			//if (compareStrings((*m_tokenIterator).getValue(), "main"))
				//postojiMain = true;
			for (labIt it1 = labele.begin(); it1 != labele.end(); it1++)
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->ime))
					throw runtime_error("\nError!" + (*m_tokenIterator).getValue() + " already declared!\n");

			l = new Labela((*m_tokenIterator).getValue(), m_brInstrukcije);
			labele.push_back(l);
			f = new Function((*m_tokenIterator).getValue());
			funkcije.push_back(f);
			break;
		case T_REG:
			++m_tokenIterator;
			if (listaRegistarskihPromenjivih.empty()) 
			{
				v = new Variable((*m_tokenIterator).getValue(), m_brRegistarskihPromenjivih);
				listaRegistarskihPromenjivih.push_back(v);
				m_brRegistarskihPromenjivih++;
			}
			else 
			{
				m_postojiUListi = false;
				for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++) 
				{
					if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName()))
						throw runtime_error("\nError! Variable "+(*m_tokenIterator).getValue()+" already declared!\n");
					
				}
				
					v = new Variable((*m_tokenIterator).getValue(), m_brRegistarskihPromenjivih);
					listaRegistarskihPromenjivih.push_back(v);
					m_brRegistarskihPromenjivih++;
			}
			
			break;
		case T_MEM:
			++m_tokenIterator;
			if (listaMemorijskihPromenjivih.empty()) 
			{
				std::string name = (*m_tokenIterator).getValue();
				++m_tokenIterator;
				double vrednost = atof((*m_tokenIterator).getValue().c_str());
				v = new Variable(name, m_brMemorijskihPromenjivih,vrednost);
				listaMemorijskihPromenjivih.push_back(v);
				m_brMemorijskihPromenjivih++;
			}
			else 
			{
				m_postojiUListi = false;
				for (varIt it1 = listaMemorijskihPromenjivih.begin(); it1 != listaMemorijskihPromenjivih.end(); it1++) 
				{
					if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName()))
						throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " already declared!\n");

				}
					std::string name = (*m_tokenIterator).getValue();
					++m_tokenIterator;
					 vrednost = atof((*m_tokenIterator).getValue().c_str());
					v = new Variable(name, m_brMemorijskihPromenjivih, vrednost);
					listaMemorijskihPromenjivih.push_back(v);
					m_brMemorijskihPromenjivih++;
			}

			break;
		case T_ADD:
			postoji = false;
			++m_tokenIterator;
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++)
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName())) 
				{
					postoji = true;
					dst.push_front((*it1));
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");
			postoji = false;
			povecajIterator(2);
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++)
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName())) 
				{
					src.push_front((*it1));
					postoji = true;
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");
			postoji = false;
			povecajIterator(2);
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++) 
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName())) 
				{
					src.push_front((*it1));
					postoji = true;
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");

			instrukcija = new Instruction(m_brInstrukcije,I_ADD,dst,src);
			listaInstrukcija.push_back(instrukcija);
			m_brInstrukcije++;
			dst.clear();
			src.clear();
			break;
		case T_ADDI:
			++m_tokenIterator;
			postoji = false;
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++) 
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName())) 
				{
					postoji = true;
					dst.push_front((*it1));
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");
			postoji = false;
			povecajIterator(2);
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++) 
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName())) 
				{
					src.push_front((*it1));
					postoji = true;
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");

			povecajIterator(2);
			vrednost = atof((*m_tokenIterator).getValue().c_str());//imm
			instrukcija = new Instruction(m_brInstrukcije, I_ADDI, dst, src,vrednost);
			listaInstrukcija.push_back(instrukcija);
			m_brInstrukcije++;
			dst.clear();
			src.clear();
			break;
		case T_B:
			m_tokenIterator++;
			instrukcija = new Instruction(m_brInstrukcije, I_B, dst, src);
			instrukcija->setImeLabele((*m_tokenIterator).getValue());
			listaInstrukcija.push_back(instrukcija);
			m_brInstrukcije++;
			break;
		case T_BLTZ:
			++m_tokenIterator;
			postoji = false;
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++) 
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName())) 
				{
					src.push_front((*it1));
					postoji = true;
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");

			povecajIterator(2);//nalazimo se na labeli
			instrukcija = new Instruction(m_brInstrukcije, I_BLTZ, dst, src);
			instrukcija->setImeLabele((*m_tokenIterator).getValue());
			listaInstrukcija.push_back(instrukcija);
			m_brInstrukcije++;
			src.clear();
			break;
		case T_LA:
			++m_tokenIterator;
			postoji = false;
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++) 
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName()))
				{
					postoji = true;
					dst.push_front((*it1));
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");
			
			postoji = false;
			povecajIterator(2);

			for (varIt it1 = listaMemorijskihPromenjivih.begin(); it1 != listaMemorijskihPromenjivih.end(); it1++)
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName()))
				{
					postoji = true;
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");

			instrukcija = new Instruction(m_brInstrukcije, I_LA, dst, src);
			
			instrukcija->setImeMemorijskePromenjive((*m_tokenIterator).getValue());
			listaInstrukcija.push_back(instrukcija);
			m_brInstrukcije++;
			dst.clear();
			break;
		case T_LI:
			++m_tokenIterator;
			postoji = false;
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++)
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName())) 
				{
					postoji = true;
					dst.push_front((*it1));
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");

			povecajIterator(2);
			vrednost = atof((*m_tokenIterator).getValue().c_str());//imm
			instrukcija = new Instruction(m_brInstrukcije, I_LI, dst, src,vrednost);
			listaInstrukcija.push_back(instrukcija);
			m_brInstrukcije++;
			dst.clear();
			break;
		case T_LW:
			++m_tokenIterator;
			postoji = false;
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++) 
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName())) 
				{
					dst.push_front((*it1));
					postoji = true;
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");
			postoji = false;
			povecajIterator(2);
			vrednost = atof((*m_tokenIterator).getValue().c_str());//offset
			povecajIterator(2);
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++) 
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName())) 
				{
					postoji = true;
					src.push_front((*it1));
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");


			instrukcija = new Instruction(m_brInstrukcije, I_LW, dst, src);
			instrukcija->setOffset(vrednost);
			listaInstrukcija.push_back(instrukcija);
			m_brInstrukcije++;
			dst.clear();
			src.clear();
			
			break;
		case T_NOP:
			instrukcija = new Instruction(m_brInstrukcije, I_NOP, dst, src);
			listaInstrukcija.push_back(instrukcija);
			m_brInstrukcije++;
			
			break;
		case T_SUB:
			++m_tokenIterator;
			postoji = false;
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++) 
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName())) 
				{
					postoji = true;
					dst.push_front((*it1));
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");
			postoji = false;
			povecajIterator(2);
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++)
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName())) 
				{
					postoji = true;
					src.push_front((*it1));
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");
			postoji = false;
			povecajIterator(2);
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++)
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName())) 
				{
					postoji = true;
					src.push_front((*it1));
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");

			instrukcija = new Instruction(m_brInstrukcije, I_SUB, dst, src);
			listaInstrukcija.push_back(instrukcija);
			m_brInstrukcije++;
			dst.clear();
			src.clear();
			break;
		case T_SW:
			postoji = false;
			++m_tokenIterator;
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++)
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName())) 
				{
					postoji = true;
					src.push_front((*it1));
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");
			postoji = false;
			povecajIterator(2);
			vrednost = atof((*m_tokenIterator).getValue().c_str());//offset
			povecajIterator(2);
			for (varIt it1 = listaRegistarskihPromenjivih.begin(); it1 != listaRegistarskihPromenjivih.end(); it1++)
			{
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->getName())) 
				{
					src.push_front((*it1));
					postoji = true;
					break;
				}
			}
			if (!postoji)
				throw runtime_error("\nError! Variable " + (*m_tokenIterator).getValue() + " is not declared!\n");

			instrukcija = new Instruction(m_brInstrukcije, I_SW, dst, src);
			instrukcija->setOffset(vrednost);
			listaInstrukcija.push_back(instrukcija);
			m_brInstrukcije++;
			src.clear();
			break;
		case T_ID:
			for (labIt it1 = labele.begin(); it1 != labele.end(); it1++)
				if (compareStrings((*m_tokenIterator).getValue(), (*it1)->ime))
					throw runtime_error("\nError!"+ (*m_tokenIterator).getValue()+" already declared!\n");

			l = new Labela((*m_tokenIterator).getValue(), m_brInstrukcije);
			labele.push_back(l);
			break;
		case T_END_OF_FILE:
			//if(!postojiMain)
				//throw runtime_error("\nError! Main function is missing!\n");
			break;
		default:
			break;
		}
		m_tokenIterator++;
	}
}

void CreateList::deleteList(Instructions& listaInstrukcija, Variables& listaRegistarskihPromenjivih, Variables& listaMemorijskihPromenjivih, Labels& labele, Functions& funkcije) {
	listaInstrukcija.remove_if([](Instruction* i) {delete i; return true; });
	listaRegistarskihPromenjivih.remove_if([](Variable* v) {delete v; return true;});
	listaMemorijskihPromenjivih.remove_if([](Variable* v) {delete v; return true; });
	labele.remove_if([](Labela* l) {delete l; return true; });
	funkcije.remove_if([](Function* f) {delete f; return true; });
}
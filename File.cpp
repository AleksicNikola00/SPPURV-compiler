#include "File.h"

#include <iostream>
#include <fstream>
using namespace std;

File::File(Labels& l):m_labele(l) {
	m_myFile.open("ispis.s");
}
File::~File() {
	m_myFile.close();
}
void File::printLabel(int x) {
	for (labIt it1 = m_labele.begin(); it1 != m_labele.end(); it1++) 
	{
		if ((*it1)->gdeSkociti == x) 
		{
			m_myFile << (*it1)->ime << ":" << endl;
			break;
		}
	}
}


void File::printIntoFile(Instructions& listaInstrukcija, Variables& listaRegistarskihPromenjivih, Variables& listaMemorijskihPromenjivih, Functions& listaFunkcija) {
	for (funcIt it1=listaFunkcija.begin();it1!=listaFunkcija.end();it1++) 
		m_myFile << ".globl " << (*it1)->ime << endl;
	
	m_myFile << "\n.data\n";

	for (varIt it1 = listaMemorijskihPromenjivih.begin(); it1 != listaMemorijskihPromenjivih.end(); it1++)
		m_myFile << (*it1)->getName() << ":\t\t.word " << (*it1)->getVrednost() << endl;
			
	m_myFile << endl;
	m_myFile << ".text" << endl;
	for (instIt it1 = listaInstrukcija.begin(); it1 != listaInstrukcija.end(); it1++) 
	{
		switch ((*it1)->getInstructionType())
		{
		case I_AND:
			printLabel((*it1)->getPosition());
			m_myFile << "\t\tand\t\t$t" << (*(*it1)->getDst().begin())->getAssignment();
			m_myFile << ", $t" << (*(*it1)->getSrc().rbegin())->getAssignment();
			m_myFile << ", $t" << (*(*it1)->getSrc().begin())->getAssignment() << endl;
			break;
		case I_ANDI:
			printLabel((*it1)->getPosition());
			m_myFile << "\t\tandi\t$t" << (*(*it1)->getDst().begin())->getAssignment();
			m_myFile << ", $t" << (*(*it1)->getSrc().begin())->getAssignment();
			m_myFile << ", " << (*it1)->getImm() << endl;
			break;
		case I_LB:
			printLabel((*it1)->getPosition());
			m_myFile << "\t\tlb\t\t$t" << (*(*it1)->getDst().begin())->getAssignment();
			m_myFile << ", " << (*it1)->getOffset() << "($t" << (*(*it1)->getSrc().begin())->getAssignment() << ")" << endl;
			break;
		case I_ADD:
			printLabel((*it1)->getPosition());
			m_myFile << "\t\tadd\t\t$t" << (*(*it1)->getDst().begin())->getAssignment();
			m_myFile << ", $t" << (*(*it1)->getSrc().rbegin())->getAssignment();
			m_myFile << ", $t" << (*(*it1)->getSrc().begin())->getAssignment() << endl;
			break;
		case I_ADDI:
			printLabel((*it1)->getPosition());
			m_myFile << "\t\taddi\t$t" << (*(*it1)->getDst().begin())->getAssignment();
			m_myFile << ", $t" << (*(*it1)->getSrc().begin())->getAssignment();
			m_myFile << ", " << (*it1)->getImm() << endl;
			break;
		case I_SUB:
			printLabel((*it1)->getPosition());
			m_myFile << "\t\tsub\t\t$t" << (*(*it1)->getDst().begin())->getAssignment();
			m_myFile << ", $t" << (*(*it1)->getSrc().rbegin())->getAssignment();
			m_myFile << ", $t" << (*(*it1)->getSrc().begin())->getAssignment() << endl;
			break;
		case I_LA:
			printLabel((*it1)->getPosition());
			m_myFile << "\t\tla\t\t$t" << (*(*it1)->getDst().begin())->getAssignment();
			m_myFile << ", " << (*it1)->getImeMemorijskePromenjive() << endl;
			break;
		case I_LI:
			printLabel((*it1)->getPosition());
			m_myFile << "\t\tli\t\t$t" << (*(*it1)->getDst().begin())->getAssignment();
			m_myFile << ", " << (*it1)->getImm() << endl;
			break;
		case I_LW:
			printLabel((*it1)->getPosition());
			m_myFile << "\t\tlw\t\t$t" << (*(*it1)->getDst().begin())->getAssignment();
			m_myFile << ", " << (*it1)->getOffset() << "($t" << (*(*it1)->getSrc().begin())->getAssignment() << ")" << endl;
			break;
		case I_SW:
			printLabel((*it1)->getPosition());
			m_myFile << "\t\tsw\t\t$t" << (*(*it1)->getSrc().rbegin())->getAssignment();
			m_myFile << ", " << (*it1)->getOffset() << "($t" << (*(*it1)->getSrc().begin())->getAssignment() << ")" << endl;
			break;
		case I_BLTZ:
			printLabel((*it1)->getPosition());
			m_myFile << "\t\tbltz\t$t" << (*(*it1)->getSrc().rbegin())->getAssignment();
			m_myFile << ", " << (*it1)->getImeLabele() << endl;
			break;
		case I_B:
			printLabel((*it1)->getPosition());
		    m_myFile << "\t\tb\t\t" << (*it1)->getImeLabele() << endl;
			break;
		default:
			printLabel((*it1)->getPosition());
			m_myFile << "\t\tnop" << endl;
		}
	}
}
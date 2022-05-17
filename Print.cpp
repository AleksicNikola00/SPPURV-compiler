#include "Print.h"
#include <iostream>

using namespace std;

void Print::printVariableslist(Variables& listaPromenjivih) {
	cout << "\nPromenjive: " << endl;
	for (varIt it1 = listaPromenjivih.begin(); it1 != listaPromenjivih.end(); it1++)
	{
		cout << "\nime: " << (*it1)->getName() << endl;
		cout << "pozicija: " << (*it1)->getPosition() << endl;
		cout << "dodeljen registar: " << (*it1)->getAssignment() << endl;
	}
}

void Print::printInstructionList(Instructions& listaInstrukcija) {
	for (instIt it1 = listaInstrukcija.begin(); it1 != listaInstrukcija.end(); it1++)
	{
		cout << "-----------------" << endl;
		cout << "Instrukcija: " << (*it1)->getPosition() << endl;
		cout << "Tip: " << (*it1)->getInstructionType() << endl;
		cout << "Def/dst list(name,position): ";
		for (varIt it2 = (*it1)->getDst().begin(); it2 != (*it1)->getDst().end(); it2++)
		{
			cout << (*it2)->getName() << "," << (*it2)->getPosition() << "    ";
		}
		cout << endl;
		cout << "Use/src list(name,position): ";
		for (varIt it2 = (*it1)->getSrc().begin(); it2 != (*it1)->getSrc().end(); it2++)
		{
			cout << (*it2)->getName() << "," << (*it2)->getPosition() << "    ";
		}
		cout << endl;
		cout << "Pred list: ";
		for (instIt it2 = (*it1)->getPred().begin(); it2 != (*it1)->getPred().end(); it2++)
		{
			cout << (*it2)->getPosition() << ", ";
		}
		cout << endl;
		cout << "Succ list: ";
		for (instIt it2 = (*it1)->getSucc().begin(); it2 != (*it1)->getSucc().end(); it2++)
		{
			cout << (*it2)->getPosition() << ", ";
		}
		cout << endl;
		cout << "In list: ";
		for (varIt it2 = (*it1)->getIn().begin(); it2 != (*it1)->getIn().end(); it2++)
		{
			cout << (*it2)->getName() << "    ";
		}
		cout << endl;
		cout << "Out list: ";
		for (varIt it2 = (*it1)->getOut().begin(); it2 != (*it1)->getOut().end(); it2++)
		{
			cout << (*it2)->getName() << "    ";
		}
		cout << endl;

	}
}

void Print::printInterferenceGraph(InterferenceGraphStruct &ig, int size) {
	cout << "\nInterference graph: " << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << ig.values[i][j] << "   ";
		}
		cout << endl;
	}
}
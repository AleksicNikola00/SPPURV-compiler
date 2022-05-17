#include "InterferenceGraph.h"

#include<iostream>

using namespace std;

void InterferenceGraph::initInterferenceGraph(InterferenceGraphStruct& ig,int size) {
	ig.values = new int*[size];

	for (int i = 0; i < size; i++)
		ig.values[i] = new int[size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			ig.values[i][j] = 0;
}

void InterferenceGraph::deleteInterferenceGraph(InterferenceGraphStruct& ig, int size) {
	for (int i = 0; i < size; i++)
		delete[] ig.values[i];

	delete[] ig.values;
}

void InterferenceGraph::createInterferenceGraph(InterferenceGraphStruct& ig, Instructions& listaInstrukcija) {
	for (instIt it1 = listaInstrukcija.begin(); it1 != listaInstrukcija.end(); it1++) 
	{
		for (varIt it2 = (*it1)->getOut().begin(); it2 != (*it1)->getOut().end(); it2++) 
		{
			if (!(*it1)->getDst().empty()) 
			{
				if ((*(*it1)->getDst().begin())->getPosition()!= (*it2)->getPosition())
				{
					ig.values[(*(*it1)->getDst().begin())->getPosition()][(*it2)->getPosition()] = 1;
					ig.values[(*it2)->getPosition()][(*(*it1)->getDst().begin())->getPosition()] = 1;
				}
			}
		}
	}
}

void InterferenceGraph::printInterferenceGraph(InterferenceGraphStruct &ig, Variables& listaPromenjivih) {
	cout << "\nInterference graph: " << endl;
	for (int i = 0; i < listaPromenjivih.size(); i++) 
	{
		for (int j = 0; j < listaPromenjivih.size(); j++) 
		{
			cout << ig.values[i][j] << "   ";
		}
		cout << endl;
	}
}
#include "LifeAnalysis.h"

#include"CreateList.h"
#include <iostream>
using namespace std;
LifeAnalysis::LifeAnalysis(){}

void LifeAnalysis::createPredAndSucc(Instructions& listaInstrukcija,Labels& listaLabela){
	int gde_skace;
	instIt pomocni_iterator;
	bool nasaoLabelu;
	for (instIt it1 = listaInstrukcija.begin(); it1 != --listaInstrukcija.end(); it1++) 
	{
			switch ((*it1)->getInstructionType())
			{
			case I_B:
				nasaoLabelu = false;
				for (labIt it2 = listaLabela.begin(); it2 != listaLabela.end(); it2++) 
				{
					if (CreateList::compareStrings((*it2)->ime,(*it1)->getImeLabele())) 
					{
						gde_skace = (*it2)->gdeSkociti;
						nasaoLabelu = true;
						break;
					}
				}
				if (!nasaoLabelu)
					throw runtime_error("\nLabel not found! Label name: '" + (*it1)->getImeLabele() + "'\n");

				for (instIt it3 = listaInstrukcija.begin(); it3 != listaInstrukcija.end(); it3++) 
				{
					if ((*it3)->getPosition() == gde_skace) 
					{
						(*it1)->pushSucc(*it3);
						(*it3)->pushPred(*it1);
						break;
					}
				}
				break;
			case I_BLTZ:
				nasaoLabelu = false;
				for (labIt it2 = listaLabela.begin(); it2 != listaLabela.end(); it2++) 
				{
					if (CreateList::compareStrings((*it2)->ime, (*it1)->getImeLabele())) 
					{
						gde_skace = (*it2)->gdeSkociti;
						nasaoLabelu = true;
						break;
					}
				}
				if (!nasaoLabelu)
					throw runtime_error("\nLabel not found! Label name: " + (*it1)->getImeLabele() + "!\n");

				for (instIt it3 = listaInstrukcija.begin(); it3 != listaInstrukcija.end(); it3++) 
				{
					if ((*it3)->getPosition() == gde_skace) 
					{
						(*it1)->pushSucc(*it3);
						(*it3)->pushPred(*it1);
						break;
					}
				}
				 pomocni_iterator = it1;
				++pomocni_iterator;
				(*it1)->pushSucc(*pomocni_iterator);
				(*pomocni_iterator)->pushPred(*it1);
				break;
			default:
				pomocni_iterator = it1;
				++pomocni_iterator;
				(*it1)->pushSucc(*pomocni_iterator);
				(*pomocni_iterator)->pushPred(*it1);
				break;
			}
	}
}

bool LifeAnalysis::variableExists(Variable*& var, Variables& listVar) {
	for (varIt it = listVar.begin(); it != listVar.end(); it++ ) 
	{
		if (var->getPosition() == (*it)->getPosition())
			return true;
	}
	return false;
}

void LifeAnalysis::livenessAnalysis(Instructions& listInstrukcija) {
	Variables copyIn, copyOut;
	bool kraj = true;;

	while (kraj)
	{
		kraj = false;
		for (instRit it = listInstrukcija.rbegin(); it != listInstrukcija.rend(); it++)
		{

			copyIn = (*it)->getIn();
			copyOut = (*it)->getOut();

			//out
			for (instRit it1 = (*it)->getSucc().rbegin(); it1 != (*it)->getSucc().rend(); it1++)
			{
				(*it)->getOut().insert((*it)->getOut().begin(), (*it1)->getIn().begin(), (*it1)->getIn().end());
			}

			//in
			(*it)->getIn().insert((*it)->getIn().begin(), (*it)->getSrc().begin(), (*it)->getSrc().end());
			for (varIt varIterator = (*it)->getOut().begin(); varIterator != (*it)->getOut().end(); varIterator++)
			{
				if (!variableExists((*varIterator), (*it)->getDst())) 
				{
					(*it)->getIn().push_back((*varIterator));
				}
			}

			(*it)->getIn().sort();
			(*it)->getOut().sort();
			(*it)->getIn().unique();
			(*it)->getOut().unique();

			//provere da li su skupovi svakog cvora kompletirani
			if ((*it)->getIn() != copyIn || (*it)->getOut() != copyOut) 
			{
				kraj = true;
			}
		}
	}

}
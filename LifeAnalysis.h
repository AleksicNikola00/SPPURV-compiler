#pragma once
#include "IR.h"

class LifeAnalysis {
public:
	LifeAnalysis();
	void createPredAndSucc(Instructions& listaInstrukcija, Labels& listaLabela);
	void livenessAnalysis(Instructions& listInstrukcija);
	bool variableExists(Variable*& var,Variables& listVar);
private:
	
	
};
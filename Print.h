#pragma once

#include "IR.h"

class Print{
private:
public:
	void printVariableslist(Variables& listaPromenjivih);
	void printInstructionList(Instructions& listaInstrukcija);
	void printInterferenceGraph(InterferenceGraphStruct &ig, int size);
};
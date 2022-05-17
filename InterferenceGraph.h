#pragma once
#include"IR.h"

class InterferenceGraph {
private:
public:
	void initInterferenceGraph(InterferenceGraphStruct& ig,int size);
	void deleteInterferenceGraph(InterferenceGraphStruct& ig, int size);
	void createInterferenceGraph(InterferenceGraphStruct& ig,Instructions& listaInstrukcija);
	void printInterferenceGraph(InterferenceGraphStruct &ig, Variables& listaPromenjivih);
};
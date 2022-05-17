#pragma once
#include"IR.h"
#define MAX_REG_NUM 4

class ResourceAllocation {
private:
public:
	bool doResourceAllocation(Stack* simplificationStack, InterferenceGraphStruct& ig);
	void createStack(Stack& simplificationStack, Variables& listaPromenjivih, InterferenceGraphStruct& ig);
	bool removeFromVector(int x, std::vector<std::vector<int>>& vektor);
	void pushToStack(int x, Variables& listaPromenjivih, Stack& simplificationStack);
};
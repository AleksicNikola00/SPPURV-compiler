#include"ResourceAllocation.h"

#include <vector>
#include<iostream>

using namespace std;
typedef std::vector<Variable*>::iterator vecIt;


bool ResourceAllocation::doResourceAllocation(Stack* simplificationStack, InterferenceGraphStruct& ig) {
	bool nijeDodeljen;
	std::vector<Variable*> v1;//vektor u koji smestamo promenjive koje pop-ujemo sa steka
	int i = 0;//brojac Regs-a

	while (!simplificationStack->empty()) 
	{
		nijeDodeljen = true;
		if (v1.empty()) 
		{
			simplificationStack->top()->setAssignment(Regs(i));
			++i;
			v1.push_back(simplificationStack->top());
			simplificationStack->pop();
		}
		else 
		{
			for (vecIt it = v1.begin(); it != v1.end(); it++) 
			{
				if (ig.values[(*it)->getPosition()][simplificationStack->top()->getPosition()] == 1) 
				{
					if (i == MAX_REG_NUM)
						return false;
					simplificationStack->top()->setAssignment(Regs(i));
					++i;
					v1.push_back(simplificationStack->top());
					simplificationStack->pop();
					nijeDodeljen = false;
					break;
				}
			}
			if (nijeDodeljen) 
			{
				if (simplificationStack->top()->getAssignment() == no_assign) 
				{
					simplificationStack->top()->setAssignment(Regs(i - 1));
					v1.push_back(simplificationStack->top());
					simplificationStack->pop();
				}
			}
		}
	}
	return true;
}



bool ResourceAllocation::removeFromVector(int x, std::vector<std::vector<int>>& vektor) {
	cout << "SMESTAMO NA STEK: r" << x+1 << endl;
	for (int i = 0; i < vektor.size(); i++) 
	{
		for (auto it1 = vektor[i].begin(); it1 != vektor[i].end(); it1++) 
		{
			if ((*it1)==x)
			{
				vektor[i].erase(it1);
				break;
			}
		}
	}
	for (int i = 0; i < vektor.size(); i++)
	{
		if (vektor[i].size() != MAX_REG_NUM || *(vektor[i].begin()) != -1)
		{
			return true;
		}
	}
	return false;
	
}

void ResourceAllocation::pushToStack(int x, Variables& listaPromenjivih, Stack& simplificationStack) {
	for (varIt it1 = listaPromenjivih.begin(); it1 != listaPromenjivih.end(); it1++) {
		if ((*it1)->getPosition() == x) {
			simplificationStack.push(*it1);
		}
	}

}



void ResourceAllocation::createStack(Stack& simplificationStack, Variables& listaPromenjivih, InterferenceGraphStruct& ig) {
	vector<vector<int>> vektorInterferencije;
	vector<int> pomocniVektor;
	varIt pomocniIterator;
	bool kraj = true;
	for (varIt it1 = listaPromenjivih.begin(); it1 != listaPromenjivih.end(); it1++)
	{
		for (varIt it2 = listaPromenjivih.begin(); it2 != listaPromenjivih.end(); it2++) 
		{
			if (ig.values[(*it1)->getPosition()][(*it2)->getPosition()] == 1)
				pomocniVektor.push_back((*it2)->getPosition());

		}
		vektorInterferencije.push_back(pomocniVektor);
		pomocniVektor.clear();
	}
	
	bool ponovi;

	while (kraj)
	{
		ponovi = false;
		for (int i = 0; i < vektorInterferencije.size(); i++)
		{
			if (vektorInterferencije[i].size() == MAX_REG_NUM - 1)
			{
				vektorInterferencije[i].resize(MAX_REG_NUM);
				fill(vektorInterferencije[i].begin(), vektorInterferencije[i].end(), -1);
				kraj=removeFromVector(i, vektorInterferencije);
				pushToStack(i , listaPromenjivih, simplificationStack);
				ponovi = true;
				break;
			}
		}
		for (int i = 0; i < vektorInterferencije.size(); i++) 
		{
			if (ponovi)
				break;
			if (vektorInterferencije[i].size() == MAX_REG_NUM - 2) 
			{
				vektorInterferencije[i].resize(MAX_REG_NUM);
				fill(vektorInterferencije[i].begin(), vektorInterferencije[i].end(), -1);
				kraj=removeFromVector(i, vektorInterferencije);
				pushToStack(i, listaPromenjivih, simplificationStack);
				ponovi = true;
				break;
			}
		}
		for (int i = 0; i < vektorInterferencije.size(); i++) 
		{
			if (ponovi)
				break;
			if (vektorInterferencije[i].size() == MAX_REG_NUM - 3) 
			{
				vektorInterferencije[i].resize(MAX_REG_NUM);
				fill(vektorInterferencije[i].begin(), vektorInterferencije[i].end(), -1);
				kraj = removeFromVector(i, vektorInterferencije);
				pushToStack(i, listaPromenjivih, simplificationStack);
				ponovi = true;
				break;
			}
		}
		for (int i = 0; i < vektorInterferencije.size(); i++) 
		{
			if (ponovi)
				break;
			if (vektorInterferencije[i].size() ==MAX_REG_NUM -4) 
			{
				vektorInterferencije[i].resize(MAX_REG_NUM);
				fill(vektorInterferencije[i].begin(), vektorInterferencije[i].end(), -1);
				kraj = removeFromVector(i, vektorInterferencije);
				pushToStack(i, listaPromenjivih, simplificationStack);
				ponovi = true;
				break;
			}
		}
		if (!ponovi) 
		{
			throw runtime_error("\nException! resource allocation failed!\n");
		}

	}
}




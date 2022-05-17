#pragma once
#include "IR.h"
#include <fstream>

class File {
private:
	std::ofstream m_myFile;
	Labels m_labele;
public:
	File(Labels &l);
	~File();
	void printIntoFile(Instructions& listaInstrukcija, Variables& listaRegistarskihPromenjivih, Variables& listaMemorijskihPromenjivih,Functions& listaFunkcija);
	void printLabel(int x);
};
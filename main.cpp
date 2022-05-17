#include <iostream>
#include <exception>


#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"
#include "IR.h"
#include "CreateList.h"
#include "LifeAnalysis.h"
#include "InterferenceGraph.h"
#include "ResourceAllocation.h"
#include "File.h"
#include "Print.h"

using namespace std;


int main()
{
	LexicalAnalysis lex;
	Instructions listaInstrukcija;
	Variables listaRegistarskihPromenjivih;
	Variables listaMemorijskihPromenjivih;
	Labels listaLabela;
	Functions listaFunkcija;
	try
	{
		
		std::string fileName = ".\\..\\examples\\simple.mavn";
		bool retVal = false;


		if (!lex.readInputFile(fileName))
			throw runtime_error("\nException! Failed to open input file!\n");

		lex.initialize();

		retVal = lex.Do();

		if (retVal)
		{
			cout << "Lexical analysis finished successfully!" << endl;
		}
		else
		{
			lex.printLexError();
			throw runtime_error("\nException! Lexical analysis failed!\n");
		}

		//sintaksni analizator
		SyntaxAnalysis syx(lex);
		retVal = syx.Do();
		if (retVal) {
			cout << "Syntax analysis finished successfully!" << endl;
		}
		else {
			throw runtime_error("\nException! Syntax analysis failed!\n");
		}
		
		//kreiranje lista
		CreateList cl(lex);
		cl.doList(listaInstrukcija, listaRegistarskihPromenjivih, listaMemorijskihPromenjivih, listaLabela,listaFunkcija);
		
		//odredjivanje skupova in/out,prethodnih/naslednik
		LifeAnalysis la;
		la.createPredAndSucc(listaInstrukcija, listaLabela);
		la.livenessAnalysis(listaInstrukcija);

		//pravljenje grafa interferencije
		InterferenceGraphStruct ig;
		InterferenceGraph iGraph;
		iGraph.initInterferenceGraph(ig, listaRegistarskihPromenjivih.size());
	    iGraph.createInterferenceGraph(ig, listaInstrukcija);
		
		//kreiranje steka simplifikacije i dodela registara
		Stack simplificationStack;
		ResourceAllocation ra;
		ra.createStack(simplificationStack, listaRegistarskihPromenjivih,ig);
		retVal=ra.doResourceAllocation(&simplificationStack,ig);
		if(!retVal)
			throw runtime_error("\nException! resource allocation failed!\n");

		//kontrolni ispis
		Print p;
		p.printInstructionList(listaInstrukcija);
		p.printInterferenceGraph(ig, listaRegistarskihPromenjivih.size());
		p.printVariableslist(listaRegistarskihPromenjivih);
		

		//ispis u fajl
		File f(listaLabela);
		f.printIntoFile(listaInstrukcija, listaRegistarskihPromenjivih, listaMemorijskihPromenjivih,listaFunkcija);

		//brisanje alocirane memorije
		iGraph.deleteInterferenceGraph(ig, listaRegistarskihPromenjivih.size());
		cl.deleteList(listaInstrukcija, listaRegistarskihPromenjivih, listaMemorijskihPromenjivih, listaLabela, listaFunkcija);
		
	}
	catch (runtime_error e)
	{
		//brisanje alocirane memorije
		CreateList c(lex);
		c.deleteList(listaInstrukcija, listaRegistarskihPromenjivih, listaMemorijskihPromenjivih, listaLabela, listaFunkcija);
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}

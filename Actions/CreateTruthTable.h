#pragma once

#include "Action.h"

#include <string>
#include <vector>

class SWITCH;
class LED;

class CreateTruthTable: public Action
{
private:
    virtual void ReadActionParameters();
	void CreateAllCombinations(std::string s = "");
	void SetSWITCHsValues(std::string Combination);
	void GetSWITCHsValues();
	void GetLEDsResults();
	void CreateTable();
	void PrintTruthTableInFile();
	void PrintTruthTableOnScreen();
	std::vector<SWITCH*> SWITCHs;
	std::vector<LED*> LEDs;
	std::vector<std::string> Combinations;
	std::vector<std::string> Lables;
	std::vector<std::string> Results;
	std::vector< std::vector<std::string> >Table;
	std::string OriginalSWITCHsData;

public:
    CreateTruthTable(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

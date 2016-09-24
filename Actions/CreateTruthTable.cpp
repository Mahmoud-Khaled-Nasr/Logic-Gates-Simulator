#include "CreateTruthTable.h"

#include "../ApplicationManager.h"
#include "../Components/SWITCH.h"
#include "../Components/LED.h"

#include <iomanip>
#include <exception>

CreateTruthTable::CreateTruthTable(ApplicationManager *pApp): Action(pApp) {}

void CreateTruthTable::ReadActionParameters()
{
    SWITCHs = pManager->GetSWITCHs();
	LEDs = pManager->GetLEDs();
}

void CreateTruthTable::Execute()
{
	ReadActionParameters();
	for (unsigned int i = 0; i < SWITCHs.size(); i++)
		Lables.push_back(SWITCHs[i]->GetLabel());
	for (unsigned int i = 0; i < LEDs.size(); i++)
		Lables.push_back(LEDs[i]->GetLabel());
	GetSWITCHsValues();
	pManager->ResetComponents();
	CreateAllCombinations();
	CreateTable();
	SetSWITCHsValues(OriginalSWITCHsData);
	pManager->ResetComponents();
	pManager->SimulateComponents();
	PrintTruthTableInFile();
	if (SWITCHs.size() <= 4)
		PrintTruthTableOnScreen();
}

void CreateTruthTable::Undo() {}

void CreateTruthTable::Redo() {}

void CreateTruthTable::CreateAllCombinations(std::string s)
{
	if (s.length() == SWITCHs.size())
	{
		SetSWITCHsValues(s);
		Combinations.push_back(s);
		pManager->SimulateComponents();
		GetLEDsResults();
		pManager->ResetComponents();
		return;
	}
	CreateAllCombinations(s + "0");
	CreateAllCombinations(s + "1");
}

void CreateTruthTable::SetSWITCHsValues(std::string Combination)
{
	for (unsigned int i = 0; i < SWITCHs.size(); i++)
		SWITCHs[i]->SetSignal((Combination[i] == '0') ? LOW : HIGH);
}

void CreateTruthTable::GetSWITCHsValues()
{
	OriginalSWITCHsData = "";
	for (unsigned int i = 0; i < SWITCHs.size(); i++)
		OriginalSWITCHsData += ((SWITCHs[i]->GetStatus() == ON) ? '1' : '0');

}

void CreateTruthTable::GetLEDsResults()
{
	std::string temp = "";
	for (unsigned int i = 0; i < LEDs.size(); i++)
		temp += ((LEDs[i]->GetStatus() == ON) ? '1' : '0');
	Results.push_back(temp);
}

void CreateTruthTable::CreateTable()
{
	Table.resize(Combinations.size()+1, std::vector<std::string>(Lables.size()));

	for (unsigned int i = 0; i < Lables.size(); i++)
		Table[0][i] = Lables[i];

	for (unsigned int k = 1; k < Combinations.size() + 1; k++)
	{
		for (unsigned int i = 0; i < SWITCHs.size(); i++)
			Table[k][i] = Combinations[k - 1][i];
		for (unsigned int j = SWITCHs.size(); j < LEDs.size() + SWITCHs.size(); j++)
			Table[k][j] = Results[k - 1][j - SWITCHs.size()];
	}
}

void CreateTruthTable::PrintTruthTableInFile()
{
	std::ofstream File;
	File.open("TruthTable.txt");
	if (! File.is_open())
		throw "Cannot open TruthTable file";

	for (unsigned int i = 0; i < Table.size(); i++)
	{
		for (unsigned int j = 0; j < Table.front().size(); j++)
		{
			File << std::setw(10) << std::left << Table[i][j];
			if (j == SWITCHs.size() - 1)
				File << std::setw(10) << std::left << "|";
		}
		File << std::endl;
	}
	File.close();
}

void CreateTruthTable::PrintTruthTableOnScreen()
{
	///TODO
}

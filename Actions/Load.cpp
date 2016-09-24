#include "Load.h"

#include "../ApplicationManager.h"
#include "../Components/BUFFER.h"
#include "../Components/NOT.h"
#include "../Components/AND2.h"
#include "../Components/NAND2.h"
#include "../Components/OR2.h"
#include "../Components/NOR2.h"
#include "../Components/XOR2.h"
#include "../Components/XNOR2.h"
#include "../Components/AND3.h"
#include "../Components/NAND3.h"
#include "../Components/OR3.h"
#include "../Components/NOR3.h"
#include "../Components/XOR3.h"
#include "../Components/XNOR3.h"
#include "../Components/SWITCH.h"
#include "../Components/LED.h"
#include "../Components/Connection.h"

#include <sstream>
#include <iostream>

Load::Load(ApplicationManager *pApp): Action(pApp) {}

void Load::ReadActionParameters() {}

void Load::Execute()
{
    std::ifstream File("SavedData.txt");
    if (!File.is_open())
        return;
    pManager->CleanUp();
    Component* pComp = NULL;
    std::map<std::string,ActionType> PossibleGates;
    PossibleGates["BUFFER"] = ADD_BUFF;
    PossibleGates["NOT"] = ADD_INV;
    PossibleGates["AND2"] = ADD_AND_GATE_2;
    PossibleGates["NAND2"] = ADD_NAND_GATE_2;
    PossibleGates["OR2"] = ADD_OR_GATE_2;
    PossibleGates["NOR2"] = ADD_NOR_GATE_2;
    PossibleGates["XOR2"] = ADD_XOR_GATE_2;
    PossibleGates["XNOR2"] = ADD_XNOR_GATE_2;
    PossibleGates["AND3"] = ADD_AND_GATE_3;
    PossibleGates["NAND3"] = ADD_NAND_GATE_3;
    PossibleGates["OR3"] = ADD_OR_GATE_3;
    PossibleGates["NOR3"] = ADD_NOR_GATE_3;
    PossibleGates["XOR3"] = ADD_XOR_GATE_3;
    PossibleGates["XNOR3"] = ADD_XNOR_GATE_3;
    PossibleGates["SWITCH"] = ADD_SWITCH;
    PossibleGates["LED"] = ADD_LED;
    std::string dummy;
    File >> dummy;
    do
    {
        ActionType ActType = PossibleGates[dummy];
        int x, y, width, height;
        std::string Label;
        File >> x >> y >> width >> height >> Label;
        std::getline(File, dummy);
        switch (ActType)
        {
        case ADD_BUFF:
            pComp  = new BUFFER(GraphicsInfo(x, y, width, height), Label+dummy);
            break;
        case ADD_INV:
            pComp  = new NOT(GraphicsInfo(x, y, width, height), Label+dummy);
            break;
        case ADD_AND_GATE_2:
            pComp  = new AND2(GraphicsInfo(x, y, width, height), Label+dummy);
            break;
        case ADD_NAND_GATE_2:
            pComp  = new NAND2(GraphicsInfo(x, y, width, height), Label+dummy);
            break;
        case ADD_OR_GATE_2:
            pComp  = new OR2(GraphicsInfo(x, y, width, height), Label+dummy);
            break;
        case ADD_NOR_GATE_2:
            pComp  = new NOR2(GraphicsInfo(x, y, width, height), Label+dummy);
            break;
        case ADD_XOR_GATE_2:
            pComp  = new XOR2(GraphicsInfo(x, y, width, height), Label+dummy);
            break;
        case ADD_XNOR_GATE_2:
            pComp  = new XNOR2(GraphicsInfo(x, y, width, height), Label+dummy);
            break;
        case ADD_AND_GATE_3:
            pComp  = new AND3(GraphicsInfo(x, y, width, height), Label+dummy);
            break;
        case ADD_NAND_GATE_3:
            pComp  = new NAND3(GraphicsInfo(x, y, width, height), Label+dummy);
            break;
        case ADD_OR_GATE_3:
            pComp  = new OR3(GraphicsInfo(x, y, width, height), Label+dummy);
            break;
        case ADD_NOR_GATE_3:
            pComp  = new NOR3(GraphicsInfo(x, y, width, height), Label+dummy);
            break;
        case ADD_XOR_GATE_3:
            pComp  = new XOR3(GraphicsInfo(x, y, width, height), Label+dummy);
            break;
        case ADD_XNOR_GATE_3:
            pComp  = new XNOR3(GraphicsInfo(x, y, width, height), Label+dummy);
            break;
        case ADD_SWITCH:
            pComp  = new SWITCH(GraphicsInfo(x, y, width, height), Label+dummy);
            break;
        case ADD_LED:
            pComp  = new LED(GraphicsInfo(x, y, width, height), Label+dummy);
            break;
        default:
            break;
        }
        pManager->AddComponent(pComp);
        File >> dummy;
    } while (dummy != "Connections");
    std::getline(File, dummy);
    do
    {
        std::getline(File, dummy);
        if (dummy == "-1")
            return;
        std::stringstream ss(dummy);
        std::vector< std::pair<int,int> > Path;
        std::pair<int,int> Point;
        while (ss >> Point.first)
        {
            ss >> Point.second;
            Path.push_back(Point);
        }
        pComp = new Connection(pManager->GetPinAt(Path.back()), pManager->GetPinAt(Path.front()), Path);
        pManager->AddComponent(pComp);
    } while (dummy != "");
}

void Load::Undo() {}

void Load::Redo() {}

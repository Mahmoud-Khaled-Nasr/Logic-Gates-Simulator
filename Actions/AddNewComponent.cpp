#include "AddNewComponent.h"

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

AddNewComponent::AddNewComponent(ApplicationManager *pApp, ActionType r_ActionType): Action(pApp)
{
	m_ActionType = r_ActionType;
}

void AddNewComponent::ReadActionParameters()
{
	std::string FilePath;
	Center = std::pair<int, int>(-1, -1);
	switch (m_ActionType)
	{
	case ADD_BUFF:
	    FilePath = "BUFFER";
		break;
	case ADD_INV:
		FilePath = "NOT";
		break;
	case ADD_AND_GATE_2:
		FilePath = "AND2";
		break;
	case ADD_NAND_GATE_2:
		FilePath = "NAND2";
		break;
	case ADD_OR_GATE_2:
		FilePath = "OR2";
		break;
	case ADD_NOR_GATE_2:
		FilePath = "NOR2";
		break;
	case ADD_XOR_GATE_2:
		FilePath = "XOR2";
		break;
	case ADD_XNOR_GATE_2:
		FilePath = "XNOR2";
		break;
	case ADD_AND_GATE_3:
		FilePath = "AND3";
		break;
	case ADD_NAND_GATE_3:
		FilePath = "NAND3";
		break;
	case ADD_OR_GATE_3:
		FilePath = "OR3";
		break;
	case ADD_NOR_GATE_3:
		FilePath = "NOR3";
		break;
	case ADD_XOR_GATE_3:
		FilePath = "XOR3";
		break;
	case ADD_XNOR_GATE_3:
		FilePath = "XNOR3";
		break;
	case ADD_SWITCH:
		FilePath = "SWITCH";
		break;
	case ADD_LED:
		FilePath = "LED";
		break;
	default:
		return;
	}
	pManager->GetInterface()->SetBusy(true);
	do
	{
		std::pair<int,int> Position = pManager->GetInterface()->GetMousePosition();
		Center = pManager->GetInterface()->GetInstantClick();
		pManager->UpdateInterface();
		if (pManager->IsValidCenter(Position))
            pManager->GetInterface()->DrawComponent(GraphicsInfo(Position.first-6, Position.second-6, 12, 12), FilePath, NORMAL);
		else
            pManager->GetInterface()->DrawComponent(GraphicsInfo(Position.first-6, Position.second-6, 12, 12), FilePath, INVALID);
        pManager->GetInterface()->ResetWindow();
        pManager->GetInterface()->SetMouseStatus(Interface::HIDDEN);
        pManager->GetInterface()->PrintMsg("Choose a position");
        pManager->SyncInterface();
	} while (Center.first == -1 && Center.second == -1);
	pManager->GetInterface()->SetBusy(false);
	pManager->GetInterface()->SetMouseStatus(Interface::POINTER);
}

void AddNewComponent::Execute()
{
	ReadActionParameters();
	if ((Center.first == -1 && Center.second == -1) || !(pManager->IsValidCenter(Center)))
		return;
	switch (m_ActionType)
	{
	case ADD_BUFF:
		pComp  = new BUFFER((GraphicsInfo(Center.first - 6, Center.second - 6, 12, 12)));
		break;
	case ADD_INV:
		pComp  = new NOT((GraphicsInfo(Center.first - 6, Center.second - 6, 12, 12)));
		break;
	case ADD_AND_GATE_2:
		pComp  = new AND2((GraphicsInfo(Center.first - 6, Center.second - 6, 12, 12)));
		break;
	case ADD_NAND_GATE_2:
	    pComp  = new NAND2((GraphicsInfo(Center.first - 6, Center.second - 6, 12, 12)));
		break;
	case ADD_OR_GATE_2:
	    pComp  = new OR2((GraphicsInfo(Center.first - 6, Center.second - 6, 12, 12)));
		break;
	case ADD_NOR_GATE_2:
	    pComp  = new NOR2((GraphicsInfo(Center.first - 6, Center.second - 6, 12, 12)));
		break;
	case ADD_XOR_GATE_2:
	    pComp  = new XOR2((GraphicsInfo(Center.first - 6, Center.second - 6, 12, 12)));
		break;
	case ADD_XNOR_GATE_2:
	    pComp  = new XNOR2((GraphicsInfo(Center.first - 6, Center.second - 6, 12, 12)));
		break;
	case ADD_AND_GATE_3:
	    pComp  = new AND3((GraphicsInfo(Center.first - 6, Center.second - 6, 12, 12)));
		break;
	case ADD_NAND_GATE_3:
	    pComp  = new NAND3((GraphicsInfo(Center.first - 6, Center.second - 6, 12, 12)));
		break;
	case ADD_OR_GATE_3:
	    pComp  = new OR3((GraphicsInfo(Center.first - 6, Center.second - 6, 12, 12)));
		break;
	case ADD_NOR_GATE_3:
	    pComp  = new NOR3((GraphicsInfo(Center.first - 6, Center.second - 6, 12, 12)));
		break;
	case ADD_XOR_GATE_3:
	    pComp  = new XOR3((GraphicsInfo(Center.first - 6, Center.second - 6, 12, 12)));
		break;
	case ADD_XNOR_GATE_3:
	    pComp  = new XNOR3((GraphicsInfo(Center.first - 6, Center.second - 6, 12, 12)));
		break;
	case ADD_SWITCH:
	    pComp  = new SWITCH((GraphicsInfo(Center.first - 6, Center.second - 6, 12, 12)));
		break;
	case ADD_LED:
	    pComp  = new LED((GraphicsInfo(Center.first - 6, Center.second - 6, 12, 12)));
		break;
	default:
		break;
	}
	pManager->AddComponent(pComp);
	pManager->AddCompletedAction(new AddNewComponent(*this));
}

void AddNewComponent::Undo()
{
	pManager->RemoveComponent(pComp);
}

void AddNewComponent::Redo()
{
	pManager->AddComponent(pComp);
}

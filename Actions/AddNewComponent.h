#pragma once

#include "../Enums.h"
#include "Action.h"

#include <string>

class Component;

class AddNewComponent: public Action
{
private:
	ActionType m_ActionType;
	std::pair<int,int> Center;
	Component* pComp;
	virtual void ReadActionParameters();

public:
    AddNewComponent(ApplicationManager *pApp, ActionType r_ActionType);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

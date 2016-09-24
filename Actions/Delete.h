#pragma once

#include "Action.h"

#include<set>

class Component;

class Delete : public Action
{
private:
	virtual void ReadActionParameters();
	std::set<Component*> Components;

public:
	Delete(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

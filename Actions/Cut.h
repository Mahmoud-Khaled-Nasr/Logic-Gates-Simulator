#pragma once

#include "Action.h"

#include <set>

class Component;

class Cut: public Action
{
private:
    std::set<Component*> Components;
    virtual void ReadActionParameters();

public:
    Cut(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

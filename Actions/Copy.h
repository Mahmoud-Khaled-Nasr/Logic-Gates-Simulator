#pragma once

#include "Action.h"

#include <set>

class Component;

class Copy: public Action
{
private:
    std::set<Component*> Components;
    virtual void ReadActionParameters();

public:
    Copy(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

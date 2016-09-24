#pragma once

#include "Action.h"

class Component;

class SwitchSignal: public Action
{
private:
    Component* pComp;
    virtual void ReadActionParameters();

public:
    SwitchSignal(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

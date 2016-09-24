#pragma once

#include "Action.h"

class Component;
class Pin;

class HandleLeftClick: public Action
{
private:
    Component* pComp;
    Pin* pPin;
    virtual void ReadActionParameters();

public:
    HandleLeftClick(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

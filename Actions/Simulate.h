#pragma once

#include "Action.h"

class Simulate: public Action
{
private:
    virtual void ReadActionParameters();

public:
    Simulate(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#pragma once

#include "Action.h"

class Add: public Action
{
private:
    virtual void ReadActionParameters();

public:
    Add(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

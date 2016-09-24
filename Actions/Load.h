#pragma once

#include "Action.h"

class Load: public Action
{
private:
    virtual void ReadActionParameters();

public:
    Load(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

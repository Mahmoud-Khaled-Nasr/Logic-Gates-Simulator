#pragma once

#include "Action.h"

class Save: public Action
{
private:
    virtual void ReadActionParameters();

public:
    Save(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

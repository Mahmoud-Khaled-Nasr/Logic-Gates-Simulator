#pragma once

#include "Action.h"

class RedoAction: public Action
{
private:
    virtual void ReadActionParameters();

public:
    RedoAction(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

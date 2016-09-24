#pragma once

#include "Action.h"

class UndoAction: public Action
{
private:
    virtual void ReadActionParameters();

public:
    UndoAction(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

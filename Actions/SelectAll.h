#pragma once

#include "Action.h"

class SelectAll: public Action
{
private:
    virtual void ReadActionParameters();

public:
    SelectAll(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

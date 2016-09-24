#pragma once

#include "Action.h"

class Stop: public Action
{
private:
    virtual void ReadActionParameters();

public:
    Stop(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

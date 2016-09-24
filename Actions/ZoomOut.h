#pragma once

#include "Action.h"

class ZoomOut: public Action
{
private:
    virtual void ReadActionParameters();

public:
    ZoomOut(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

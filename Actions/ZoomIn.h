#pragma once

#include "Action.h"

class ZoomIn: public Action
{
private:
    virtual void ReadActionParameters();

public:
    ZoomIn(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

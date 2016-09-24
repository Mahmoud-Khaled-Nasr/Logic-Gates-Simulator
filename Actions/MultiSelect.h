#pragma once

#include "Action.h"

class MultiSelect: public Action
{
private:
    virtual void ReadActionParameters();
    int MaxLeft, MaxRight, MaxUp, MaxDown;

public:
    MultiSelect(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

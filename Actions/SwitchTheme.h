#pragma once

#include "Action.h"

class SwitchTheme: public Action
{
private:
    virtual void ReadActionParameters();

public:
    SwitchTheme(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

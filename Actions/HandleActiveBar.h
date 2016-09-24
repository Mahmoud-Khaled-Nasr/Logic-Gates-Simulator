#pragma once

#include "Action.h"

class Button;

class HandleActiveBar: public Action
{
private:
    Button* TargetButton;
    virtual void ReadActionParameters();

public:
    HandleActiveBar(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

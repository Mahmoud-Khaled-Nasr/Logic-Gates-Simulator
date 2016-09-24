#pragma once

#include "Action.h"

#include <vector>

class Component;

class Paste: public Action
{
private:
    std::vector<Component*> Clipboard;
    std::pair<int, int> Delta;
    virtual void ReadActionParameters();

public:
    Paste(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#pragma once

#include "Action.h"

#include <utility>

class AdjustOffset: public Action
{
private:
    std::pair<int,int> Base;
    virtual void ReadActionParameters();

public:
    AdjustOffset(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#pragma once

class ApplicationManager;

class Action
{
private:
    virtual void ReadActionParameters()=0;

protected:
	ApplicationManager* pManager;

public:
	Action(ApplicationManager *pApp) { pManager = pApp; }
	virtual ~Action() {}
	virtual void Execute()=0;
	virtual void Undo()=0;
	virtual void Redo()=0;
};

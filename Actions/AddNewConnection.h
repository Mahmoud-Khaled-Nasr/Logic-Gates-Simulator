#pragma once

#include "Action.h"

class Connection;
class Pin;

class AddNewConnection: public Action
{
private:
	Pin* m_InputPin;
	Pin* m_OutputPin;
	Connection* pConnection;
	virtual void ReadActionParameters();

public:
    AddNewConnection(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

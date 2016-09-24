#include "Copy.h"

#include "../ApplicationManager.h"
#include "../Components/Connection.h"

Copy::Copy(ApplicationManager *pApp): Action(pApp) {}

void Copy::ReadActionParameters()
{
	std::vector<Component*> dummyClipboard = pManager->GetClipboard();
	for (unsigned int i = 0; i < dummyClipboard.size(); i++)
		delete dummyClipboard[i];
	pManager->FlushClipboard();
	Components = pManager->GetSelectedComponents();
}

void Copy::Execute()
{
	ReadActionParameters();
	for (std::set<Component*>::iterator i = Components.begin(); i != Components.end(); i++)
		(*i)->Copy(pManager);
}

void Copy::Undo() {}

void Copy::Redo() {}

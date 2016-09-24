#include "Cut.h"

#include <vector>

#include "../ApplicationManager.h"
#include "../Components/Connection.h"

Cut::Cut(ApplicationManager *pApp): Action(pApp) {}

void Cut::ReadActionParameters()
{
	std::vector<Component*> dummyClipboard = pManager->GetClipboard();
	for (unsigned int i = 0; i < dummyClipboard.size(); i++)
		delete dummyClipboard[i];
	pManager->FlushClipboard();
	Components = pManager->GetSelectedComponents();
}

void Cut::Execute()
{
	ReadActionParameters();
	for(std::set<Component*>::iterator i = Components.begin(); i != Components.end(); i++)
		if ((*i)->WithinRegion(Components))
			pManager->PushIntoClipboard(*i);
	for(std::set<Component*>::iterator i = Components.begin(); i != Components.end(); i++)
        pManager->RemoveComponent(*i);
	pManager->AddCompletedAction(new Cut(*this));
}

void Cut::Undo()
{
	for(std::set<Component*>::iterator i = Components.begin(); i != Components.end(); i++)
        pManager->AddComponent(*i);
	pManager->FlushClipboard();
}

void Cut::Redo()
{
	for(std::set<Component*>::iterator i = Components.begin(); i != Components.end(); i++)
		if ((*i)->WithinRegion(Components))
			pManager->PushIntoClipboard(*i);
	for(std::set<Component*>::iterator i = Components.begin(); i != Components.end(); i++)
        pManager->RemoveComponent(*i);
}

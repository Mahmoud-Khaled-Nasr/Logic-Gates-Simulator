#include "Delete.h"

#include "../ApplicationManager.h"

Delete::Delete(ApplicationManager *pApp) : Action(pApp) {}

void Delete::ReadActionParameters()
{
	Components = pManager->GetSelectedComponents();
}

void Delete::Execute()
{
	ReadActionParameters();
	if (Components.empty())
        return;
	std::set<Component*> s = Components;
	for(std::set<Component*>::iterator i = Components.begin(); i != Components.end(); i++)
        pManager->RemoveComponent(*i);
	pManager->AddCompletedAction(new Delete(*this));
}

void Delete::Undo()
{
	for(std::set<Component*>::iterator i = Components.begin(); i != Components.end(); i++)
        pManager->AddComponent(*i);

}

void Delete::Redo()
{
    for(std::set<Component*>::iterator i = Components.begin(); i != Components.end(); i++)
        pManager->RemoveComponent(*i);
}

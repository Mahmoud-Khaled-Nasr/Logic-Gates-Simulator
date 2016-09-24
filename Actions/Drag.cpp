#include "Drag.h"

#include "../ApplicationManager.h"
#include "../Components/Connection.h"

Drag::Drag(ApplicationManager *pApp): Action(pApp) {}

void Drag::ReadActionParameters()
{
    std::pair<int, int> InitialPosition = pManager->GetInterface()->GetMousePosition();
    std::pair<int, int> FinalPosition;
    std::set<Component*> dummySet = pManager->GetSelectedComponents();
    for(std::set<Component*>::iterator i = dummySet.begin(); i != dummySet.end(); i++)
    {
        if ((*i)->WithinRegion(dummySet))
            Components.insert(*i);
        else
            OutOfRangeConnections.push_back(dynamic_cast<Connection*> ((*i)));
    }
    for(unsigned int i = 0; i < OutOfRangeConnections.size(); i++)
        if (OutOfRangeConnections[i] == NULL)
            throw "Non-connection out of range";
    for(unsigned int i = 0; i < OutOfRangeConnections.size(); i++)
        OldPaths.push_back(OutOfRangeConnections[i]->GetPath());

    RemoveComponents();
    RemoveOutOfRangeConnections();

    do
	{
        std::pair<int, int> Position = pManager->GetInterface()->GetMousePosition();
        ShiftComponentsBy(std::pair<int,int> (Position.first - InitialPosition.first, Position.second - InitialPosition.second));
        if (IsValid())
        {
            AddComponents();
            UpdateOutOfRangeConnections();
            AddOutOfRangeConnections();
            pManager->UpdateInterface();
            RemoveOutOfRangeConnections();
            ResetOutOfRangeConnections();
            RemoveComponents();
        }
        else
            pManager->UpdateInterface();
        pManager->GetInterface()->SetMouseStatus(Interface::DRAG);
        pManager->SyncInterface();
        ShiftComponentsBy(std::pair<int,int> (InitialPosition.first - Position.first, InitialPosition.second - Position.second));
        FinalPosition = pManager->GetInterface()->GetInstantRelease();
	} while (FinalPosition.first == -1 && FinalPosition.second == -1);
	Delta.first = FinalPosition.first - InitialPosition.first;
	Delta.second = FinalPosition.second - InitialPosition.second;
}

void Drag::Execute()
{
    ReadActionParameters();
    ShiftComponentsBy(Delta);
    if (!IsValid())
    {
        ShiftComponentsBy(std::pair<int,int> (-Delta.first, -Delta.second));
        AddComponents();
        AddOutOfRangeConnections();
        return;
    }
    AddComponents();
    UpdateOutOfRangeConnections();
    AddOutOfRangeConnections();
    pManager->AddCompletedAction(new Drag(*this));
}

void Drag::Undo()
{
    RemoveComponents();
    RemoveOutOfRangeConnections();
    ShiftComponentsBy(std::pair<int,int> (-Delta.first, -Delta.second));
    AddComponents();
    ResetOutOfRangeConnections();
    AddOutOfRangeConnections();
}

void Drag::Redo()
{
    RemoveComponents();
    RemoveOutOfRangeConnections();
    ShiftComponentsBy(Delta);
    AddComponents();
    UpdateOutOfRangeConnections();
    AddOutOfRangeConnections();
}

bool Drag::IsValid() const
{
    for(std::set<Component*>::iterator i = Components.begin(); i != Components.end(); i++)
		if (!pManager->IsValidCenter((*i)->GetCenter()))
            return false;
    return true;
}

void Drag::AddComponents()
{
    for(std::set<Component*>::iterator i = Components.begin(); i != Components.end(); i++)
        pManager->AddComponent(*i);
}

void Drag::ShiftComponentsBy(std::pair<int,int> Delta)
{
    for(std::set<Component*>::iterator i = Components.begin(); i != Components.end(); i++)
        (*i)->ShiftBy(Delta);
}

void Drag::RemoveComponents()
{
    for(std::set<Component*>::iterator i = Components.begin(); i != Components.end(); i++)
        pManager->RemoveComponent(*i);
}

void Drag::AddOutOfRangeConnections()
{
    for(unsigned int i = 0; i < OutOfRangeConnections.size(); i++)
        pManager->AddComponent(OutOfRangeConnections[i]);
}

void Drag::UpdateOutOfRangeConnections()
{
    for(unsigned int i = 0; i < OutOfRangeConnections.size(); i++)
        OutOfRangeConnections[i]->Update(pManager->FindPathThroughGrid(OutOfRangeConnections[i]->GetPinsCoordinates().first, OutOfRangeConnections[i]->GetPinsCoordinates().second));
}

void Drag::RemoveOutOfRangeConnections()
{
    for(unsigned int i = 0; i < OutOfRangeConnections.size(); i++)
        pManager->RemoveComponent(OutOfRangeConnections[i]);
}

void Drag::ResetOutOfRangeConnections()
{
    for(unsigned int i = 0; i < OutOfRangeConnections.size(); i++)
        OutOfRangeConnections[i]->Update(OldPaths[i]);
}

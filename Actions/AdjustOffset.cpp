#include "AdjustOffset.h"

#include "../ApplicationManager.h"

AdjustOffset::AdjustOffset(ApplicationManager *pApp): Action(pApp) {}

void AdjustOffset::ReadActionParameters()
{
    Base = pManager->GetInterface()->GetMousePosition(true);
}

void AdjustOffset::Execute()
{
    ReadActionParameters();
    pManager->GetInterface()->SetBusy(true);
    while (pManager->GetInterface()->IsDragging())
    {
        std::pair<int,int> dummy = pManager->GetInterface()->GetMousePosition(true);
        pManager->GetInterface()->ShiftOffsetBy(std::pair<int,int> (Base.first-dummy.first, Base.second-dummy.second));
        Base = dummy;
        pManager->UpdateInterface();
        pManager->GetInterface()->SetMouseStatus(Interface::NAVIGATION);
        pManager->SyncInterface();
    }
    pManager->GetInterface()->SetBusy(false);
}

void AdjustOffset::Undo() {}

void AdjustOffset::Redo() {}

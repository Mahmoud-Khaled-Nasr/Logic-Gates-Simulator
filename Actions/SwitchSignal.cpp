#include "SwitchSignal.h"

#include "../ApplicationManager.h"
#include "../Components/SWITCH.h"

SwitchSignal::SwitchSignal(ApplicationManager *pApp): Action(pApp) {}

void SwitchSignal::ReadActionParameters()
{
    pComp = pManager->GetComponentAt(pManager->GetInterface()->GetMousePosition());
}

void SwitchSignal::Execute()
{
    ReadActionParameters();
    SWITCH* dummy = dynamic_cast<SWITCH*> (pComp);
    if (dummy != NULL)
        dummy->SwitchSignal();
    pManager->ExecuteAction(SIMULATE);
}

void SwitchSignal::Undo() {}

void SwitchSignal::Redo() {}

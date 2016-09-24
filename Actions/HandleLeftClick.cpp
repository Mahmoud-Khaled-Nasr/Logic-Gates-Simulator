#include "HandleLeftClick.h"

#include "../ApplicationManager.h"
#include "../Components/Pin.h"

HandleLeftClick::HandleLeftClick(ApplicationManager *pApp): Action(pApp) {}

void HandleLeftClick::ReadActionParameters()
{
    pComp = pManager->GetComponentAt(pManager->GetInterface()->GetMousePosition());
    pPin = pManager->GetPinAt(pManager->GetInterface()->GetMousePosition());
}

void HandleLeftClick::Execute()
{
    ReadActionParameters();
    if (pManager->GetInterface()->IsDoubleClick())
    {
        if (pComp != NULL)
        {
            pManager->UpdateInterface();
            pManager->GetInterface()->PrintMsg("Enter new label");
            pManager->GetInterface()->SetMouseStatus(Interface::HIDDEN);
            pManager->SyncInterface();
            pComp->SetLabel(pManager->GetInterface()->GetSrting());
        }
    }
    else if (pManager->GetInterface()->IsDragging())
    {
        if (pManager->GetInterface()->IsCtrlOn())
            pManager->ExecuteAction(ADJUST_OFFSET);
        else if (!pManager->GetInterface()->IsSimulating())
        {
            if (pComp != NULL)
                pManager->ExecuteAction(DRAG);
            else
                pManager->ExecuteAction(MULTI_SELECT);
        }
    }
    else if (pManager->GetInterface()->IsSimulating())
    {
        pManager->ExecuteAction(SWITCH_SIGNAL);
    }
    else
    {
        if (pPin != NULL && pPin->IsConnectable())
            pManager->ExecuteAction(ADD_CONNECTION);
        else if (pComp != NULL)
        {
            if (pManager->GetInterface()->IsCtrlOn())
            {
                pComp->SetStatus((pComp->GetStatus() == NORMAL) ? SELECTED : NORMAL);
            }
            else
            {
                pManager->ResetComponents();
                pComp->SetStatus(SELECTED);
            }
        }
        else if (!(pManager->GetInterface()->IsCtrlOn()))
        {
            pManager->ResetComponents();
        }
    }
}

void HandleLeftClick::Undo() {}

void HandleLeftClick::Redo() {}

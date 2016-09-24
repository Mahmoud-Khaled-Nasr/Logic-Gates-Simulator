#include "HandleActiveBar.h"

#include "../ApplicationManager.h"
#include "../GUI/Button.h"

HandleActiveBar::HandleActiveBar(ApplicationManager *pApp): Action(pApp) {}

void HandleActiveBar::ReadActionParameters()
{
    const std::vector<Button*>& Buttons = pManager->GetInterface()->GetActiveButtons();
    for(unsigned int i = 0; i < Buttons.size(); i++)
        if (Buttons[i] != NULL)
            if (Buttons[i]->GetGraphicsInfo().Contains(pManager->GetInterface()->GetMousePosition(true)))
            {
                TargetButton = Buttons[i];
                return;
            }
    TargetButton = NULL;
}

void HandleActiveBar::Execute()
{
    ReadActionParameters();
    if (TargetButton == NULL)
        return;
    TargetButton->SetStatus(Interface::FOCUSED);
    pManager->GetInterface()->SetBusy(true);
    std::pair<int,int> dummy;
    pManager->UpdateInterface();
    pManager->SyncInterface();
    do
    {
        dummy = pManager->GetInterface()->GetInstantRelease(true);
        pManager->UpdateInterface();
        pManager->SyncInterface();
    } while (dummy.first == -1 && dummy.second == -1);
    TargetButton->SetStatus(Interface::NORMAL);
    pManager->GetInterface()->SetBusy(false);
    if (TargetButton->GetGraphicsInfo().Contains(dummy))
        pManager->ExecuteAction(TargetButton->GetAction());
}

void HandleActiveBar::Undo() {}

void HandleActiveBar::Redo() {}

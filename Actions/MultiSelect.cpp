#include "MultiSelect.h"

#include "../ApplicationManager.h"

MultiSelect::MultiSelect(ApplicationManager *pApp): Action(pApp) {}

void MultiSelect::ReadActionParameters()
{
    std::pair<int, int> InitialPosition = pManager->GetInterface()->GetMousePosition();
    std::pair<int, int> FinalPosition;
	do
	{
        std::pair<int, int> Position = pManager->GetInterface()->GetMousePosition();
        MaxLeft = std::min(InitialPosition.first, Position.first);
        MaxRight = std::max(InitialPosition.first, Position.first);
        MaxUp = std::min(InitialPosition.second, Position.second);
        MaxDown = std::max(InitialPosition.second, Position.second);
        pManager->UpdateInterface();
        pManager->GetInterface()->DrawSelectionRectangle(GraphicsInfo(MaxLeft, MaxUp, MaxRight-MaxLeft, MaxDown-MaxUp));
        pManager->SyncInterface();
        FinalPosition = pManager->GetInterface()->GetInstantRelease();
	} while (FinalPosition.first == -1 && FinalPosition.second == -1);
	MaxLeft = std::min(InitialPosition.first, FinalPosition.first);
    MaxRight = std::max(InitialPosition.first, FinalPosition.first);
    MaxUp = std::min(InitialPosition.second, FinalPosition.second);
    MaxDown = std::max(InitialPosition.second, FinalPosition.second);
}

void MultiSelect::Execute()
{
    ReadActionParameters();
    pManager->ResetComponents();
    for(int i = MaxLeft; i <= MaxRight; i++)
        for(int j = MaxUp; j <= MaxDown; j++)
        {
            Component* pComp = pManager->GetComponentAt(std::pair<int,int> (i,j));
            if (pComp != NULL)
                pComp->SetStatus(SELECTED);
        }
}

void MultiSelect::Undo() {}

void MultiSelect::Redo() {}

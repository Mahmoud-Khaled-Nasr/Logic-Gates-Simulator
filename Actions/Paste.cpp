#include "Paste.h"

#include "../ApplicationManager.h"

Paste::Paste(ApplicationManager *pApp): Action(pApp) {}

void Paste::ReadActionParameters()
{
	Clipboard = pManager->GetClipboard();
	if (Clipboard.empty())
		return;
	int MaxLeft = Clipboard[0]->GetCenter().first;
	int MaxRight = Clipboard[0]->GetCenter().first;
	int MaxUp = Clipboard[0]->GetCenter().second;
	int MaxDown = Clipboard[0]->GetCenter().second;
	for (unsigned int i = 0; i < Clipboard.size(); i++)
	{
        MaxLeft = std::min(MaxLeft, Clipboard[i]->GetCenter().first);
        MaxRight = std::max(MaxRight, Clipboard[i]->GetCenter().first);
        MaxUp = std::min(MaxUp, Clipboard[i]->GetCenter().second);
        MaxDown = std::max(MaxDown, Clipboard[i]->GetCenter().second);
	}
	std::pair<int, int> Center((MaxLeft + MaxRight + 1) / 2, (MaxUp + MaxDown + 1) / 2);
	std::pair<int, int> Position = pManager->GetInterface()->GetMousePosition();
	Delta.first = Position.first - Center.first;
	Delta.second = Position.second - Center.second;
}

void Paste::Execute()
{
	ReadActionParameters();
	if (Clipboard.empty())
        return;
	for (unsigned int i = 0; i < Clipboard.size(); i++)
		Clipboard[i]->ShiftBy(Delta);
	for (unsigned int i = 0; i < Clipboard.size(); i++)
		if (!pManager->IsValidCenter(Clipboard[i]->GetCenter()))
        {
            for (unsigned int i = 0; i < Clipboard.size(); i++)
                Clipboard[i]->ShiftBy(std::pair<int,int> (-Delta.first, -Delta.second));
            return;
        }
    for (unsigned int i = 0; i < Clipboard.size(); i++)
        pManager->AddComponent(Clipboard[i]);
	pManager->FlushClipboard();
	pManager->AddCompletedAction(new Paste(*this));
}

void Paste::Undo()
{
    for (unsigned int i = 0; i < Clipboard.size(); i++)
        pManager->RemoveComponent(Clipboard[i]);
    for (unsigned int i = 0; i < Clipboard.size(); i++)
		Clipboard[i]->ShiftBy(std::pair<int,int> (-Delta.first, -Delta.second));
    for (unsigned int i = 0; i < Clipboard.size(); i++)
		pManager->PushIntoClipboard(Clipboard[i]);
}

void Paste::Redo()
{
    for (unsigned int i = 0; i < Clipboard.size(); i++)
        Clipboard[i]->ShiftBy(Delta);
    for (unsigned int i = 0; i < Clipboard.size(); i++)
        pManager->AddComponent(Clipboard[i]);
    pManager->FlushClipboard();
}

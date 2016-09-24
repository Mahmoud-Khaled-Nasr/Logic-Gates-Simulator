#include "SelectAll.h"

#include "../ApplicationManager.h"

SelectAll::SelectAll(ApplicationManager *pApp): Action(pApp) {}

void SelectAll::ReadActionParameters() {}

void SelectAll::Execute()
{
    pManager->SelectAllComponents();
}

void SelectAll::Undo() {}

void SelectAll::Redo() {}

#include "UndoAction.h"

#include "../ApplicationManager.h"

UndoAction::UndoAction(ApplicationManager *pApp): Action(pApp) {}

void UndoAction::ReadActionParameters() {}

void UndoAction::Execute()
{
    pManager->UndoCompletedAction();
}

void UndoAction::Undo() {}

void UndoAction::Redo() {}

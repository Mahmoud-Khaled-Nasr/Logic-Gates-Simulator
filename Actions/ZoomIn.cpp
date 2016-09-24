#include "ZoomIn.h"

#include "../ApplicationManager.h"

ZoomIn::ZoomIn(ApplicationManager *pApp): Action(pApp) {}

void ZoomIn::ReadActionParameters() {}

void ZoomIn::Execute()
{
    pManager->GetInterface()->ZoomIn();
}

void ZoomIn::Undo() {}

void ZoomIn::Redo() {}

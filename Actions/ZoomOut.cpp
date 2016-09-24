#include "ZoomOut.h"

#include "../ApplicationManager.h"

ZoomOut::ZoomOut(ApplicationManager *pApp): Action(pApp) {}

void ZoomOut::ReadActionParameters() {}

void ZoomOut::Execute()
{
    pManager->GetInterface()->ZoomOut();
}

void ZoomOut::Undo() {}

void ZoomOut::Redo() {}

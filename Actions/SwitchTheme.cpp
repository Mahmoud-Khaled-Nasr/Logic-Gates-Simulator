#include "SwitchTheme.h"

#include "../ApplicationManager.h"

SwitchTheme::SwitchTheme(ApplicationManager *pApp): Action(pApp) {}

void SwitchTheme::ReadActionParameters() {}

void SwitchTheme::Execute()
{
    pManager->GetInterface()->SwitchAppTheme();
}

void SwitchTheme::Undo() {}

void SwitchTheme::Redo() {}

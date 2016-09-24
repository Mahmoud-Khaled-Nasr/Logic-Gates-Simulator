#include "Save.h"

#include "../ApplicationManager.h"

Save::Save(ApplicationManager *pApp): Action(pApp) {}

void Save::ReadActionParameters() {}

void Save::Execute()
{
    std::fstream File("SavedData.txt", std::ios::in | std::ios::out | std::ios::trunc);
    File << std::endl << "Connections" << std::endl;
    pManager->SaveComponents(File);
    File << -1 << std::endl;
    File.close();
}

void Save::Undo() {}

void Save::Redo() {}

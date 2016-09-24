#include "Simulate.h"

#include "../ApplicationManager.h"

#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)

  #include <windows.h>

  inline void delay( unsigned long ms )
    {
    Sleep( ms );
    }

#else

  #include <unistd.h>

  inline void delay( unsigned long ms )
    {
    usleep( ms * 1000 );
    }

#endif

Simulate::Simulate(ApplicationManager *pApp): Action(pApp) {}

void Simulate::ReadActionParameters() {}

void Simulate::Execute()
{
	pManager->ResetComponents();
	if (!pManager->AreComponentsConnected())
    {
        std::pair<int,int> Point;
        pManager->GetInterface()->SetBusy(true);
        do
        {
            pManager->UpdateInterface();
            pManager->GetInterface()->PrintMsg("Circuit NOT connected, Click any where to continue...");
            pManager->SyncInterface();
            Point = pManager->GetInterface()->GetInstantClick();
        } while (Point.first == -1 && Point.second == -1);
        pManager->GetInterface()->SetBusy(false);
        return;
    }
	if (!pManager->SimulateComponents())
	{
        std::pair<int,int> Point;
        pManager->GetInterface()->SetBusy(true);
        do
        {
            pManager->UpdateInterface();
            pManager->GetInterface()->PrintMsg("Infinite loop, Click any where to continue...");
            pManager->SyncInterface();
            Point = pManager->GetInterface()->GetInstantClick();
        } while (Point.first == -1 && Point.second == -1);
        pManager->GetInterface()->SetBusy(false);
        return;
    }
    if (!pManager->GetInterface()->IsSimulating())
        pManager->GetInterface()->SwitchAppMode();
}

void Simulate::Undo() {}

void Simulate::Redo() {}

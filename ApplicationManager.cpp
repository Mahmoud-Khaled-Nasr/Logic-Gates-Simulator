#include "ApplicationManager.h"

#include "Actions/Add.h"
#include "Actions/AddNewComponent.h"
#include "Actions/AddNewConnection.h"
#include "Actions/Delete.h"
#include "Actions/Drag.h"
#include "Actions/Copy.h"
#include "Actions/Cut.h"
#include "Actions/Paste.h"
#include "Actions/MultiSelect.h"
#include "Actions/SelectAll.h"
#include "Actions/HandleLeftClick.h"
#include "Actions/HandleActiveBar.h"
#include "Actions/SwitchSignal.h"
#include "Actions/Simulate.h"
#include "Actions/Stop.h"
#include "Actions/CreateTruthTable.h"
#include "Actions/UndoAction.h"
#include "Actions/RedoAction.h"
#include "Actions/Save.h"
#include "Actions/Load.h"
#include "Actions/AdjustOffset.h"
#include "Actions/ZoomIn.h"
#include "Actions/ZoomOut.h"
#include "Actions/SwitchTheme.h"
#include "Components/Component.h"
#include "Components/SWITCH.h"
#include "Components/LED.h"

#include <algorithm>

ApplicationManager::ApplicationManager(): MainInterface(360, 360), SimGrid(360, 360) {}

ApplicationManager::~ApplicationManager()
{
    CleanUp();
}

ActionType ApplicationManager::GetUserAction()
{
    return MainInterface.GetUserAction();
}

void ApplicationManager::ExecuteAction(ActionType Act)
{
    Action* dummyAction = NULL;
    switch (Act)
    {
    case ADD:
        dummyAction = new Add(this);
        break;
    case ADD_CONNECTION:
        dummyAction = new AddNewConnection(this);
        break;
	case CREATE_TRUTHTABLE:
        dummyAction = new CreateTruthTable(this);
        break;
    case ACTIVE_BAR_CLICK:
        dummyAction = new HandleActiveBar(this);
        break;
	case CANVAS_LEFT_CLICK:
        dummyAction = new HandleLeftClick(this);
        break;
	case CANVAS_RIGHT_CLICK:
        break;
    case SWITCH_SIGNAL:
        dummyAction = new SwitchSignal(this);
        break;
    case MULTI_SELECT:
        dummyAction = new MultiSelect(this);
        break;
    case SELECT_ALL:
        dummyAction = new SelectAll(this);
        break;
	case DELETE:
        dummyAction = new Delete(this);
        break;
	case DRAG:
        dummyAction = new Drag(this);
        break;
	case COPY:
        dummyAction = new Copy(this);
        break;
    case CUT:
        dummyAction = new Cut(this);
        break;
	case PASTE:
        dummyAction = new Paste(this);
        break;
	case SAVE:
        dummyAction = new Save(this);
        break;
	case LOAD:
        dummyAction = new Load(this);
        break;
	case UNDO:
        dummyAction = new UndoAction(this);
        break;
	case REDO:
        dummyAction = new RedoAction(this);
        break;
	case SIMULATE:
        dummyAction = new Simulate(this);
        break;
    case STOP:
        dummyAction = new Stop(this);
        break;
	case SWITCH_THEME:
        dummyAction = new SwitchTheme(this);
        break;
    case ADJUST_OFFSET:
        dummyAction = new AdjustOffset(this);
        break;
    case ZOOM_IN:
        dummyAction = new ZoomIn(this);
        break;
    case ZOOM_OUT:
        dummyAction = new ZoomOut(this);
        break;
	case EXIT:
	    exit(0);
        break;
	case STATUS_BAR:
        break;
	case NONE:
        break;
    default:
        dummyAction = new AddNewComponent(this, Act);
    }
    if (dummyAction != NULL)
    {
        dummyAction->Execute();
        delete dummyAction;
    }
}

void ApplicationManager::UpdateInterface()
{
    if (GetSelectedComponents().empty())
    {
        MainInterface.DisableButtonWithAction(DELETE);
        MainInterface.DisableButtonWithAction(COPY);
        MainInterface.DisableButtonWithAction(CUT);
    }
    else
    {
        MainInterface.EnableButtonWithAction(DELETE);
        MainInterface.EnableButtonWithAction(COPY);
        MainInterface.EnableButtonWithAction(CUT);
    }
    if (DoneActions.empty())
        MainInterface.DisableButtonWithAction(UNDO);
    else
        MainInterface.EnableButtonWithAction(UNDO);
    if (UndoneActions.empty())
        MainInterface.DisableButtonWithAction(REDO);
    else
        MainInterface.EnableButtonWithAction(REDO);

    MainInterface.SetTooltipText("");
    MainInterface.ClearCanvas();
    for(unsigned int i = 0; i < Components.size(); i++)
        Components[i]->Draw(&MainInterface);
    MainInterface.ResetWindow();
    MainInterface.PrintMsg("Ready!");
}

void ApplicationManager::SyncInterface()
{
    MainInterface.SyncWindow();
}

Interface* ApplicationManager::GetInterface()
{
    return &MainInterface;
}

void ApplicationManager::AddCompletedAction(Action* pAction)
{
    DoneActions.push_back(pAction);
    for(unsigned int i = 0; i < UndoneActions.size(); i++)
        delete UndoneActions[i];
    UndoneActions.clear();
}

void ApplicationManager::UndoCompletedAction()
{
    if (DoneActions.empty())
        return;
    DoneActions.back()->Undo();
    UndoneActions.push_back(DoneActions.back());
    DoneActions.pop_back();
}

void ApplicationManager::RedoUndoneAction()
{
    if (UndoneActions.empty())
        return;
    UndoneActions.back()->Redo();
    DoneActions.push_back(UndoneActions.back());
    UndoneActions.pop_back();
}

bool ApplicationManager::IsClipboardEmpty() const
{
    return Clipboard.size() == 0;
}

void ApplicationManager::PushIntoClipboard(Component* ToBeSaved)
{
    Clipboard.push_back(ToBeSaved);
}

const std::vector<Component*>& ApplicationManager::GetClipboard()
{
    return Clipboard;
}

void ApplicationManager::FlushClipboard()
{
    Clipboard.clear();
}

std::vector< std::pair<int,int> > ApplicationManager::FindPathThroughGrid(std::pair<int,int> Point1, std::pair<int,int> Point2)
{
    return SimGrid.FindPath(Point1, Point2);
}

bool ApplicationManager::IsValidCenter(std::pair<int,int> Center) const
{
    return SimGrid.IsValidCenter(Center);
}

Component* ApplicationManager::GetComponentAt(std::pair<int, int> Point)
{
    return SimGrid.GetComponentAt(Point);
}

Pin* ApplicationManager::GetPinAt(std::pair<int, int> Point)
{
    return SimGrid.GetPinAt(Point);
}

std::vector<SWITCH*> ApplicationManager::GetSWITCHs()
{
    std::vector<SWITCH*> SWITCHs;
    for(unsigned int i = 0; i < Components.size(); i++)
    {
        SWITCH* dummy = dynamic_cast<SWITCH*> (Components[i]);
        if (dummy != NULL)
            SWITCHs.push_back(dummy);
    }
    return SWITCHs;
}

std::vector<LED*> ApplicationManager::GetLEDs()
{
    std::vector<LED*> LEDs;
    for(unsigned int i = 0; i < Components.size(); i++)
    {
        LED* dummy = dynamic_cast<LED*> (Components[i]);
        if (dummy != NULL)
            LEDs.push_back(dummy);
    }
    return LEDs;
}

std::set<Component*> ApplicationManager::GetSelectedComponents()
{
    std::set<Component*> Selected;
    for(unsigned int i = 0; i < Components.size(); i++)
        if (Components[i]->GetStatus() == SELECTED)
        {
            Selected.insert(Components[i]);
            std::set<Component*> AssociatedComponents = Components[i]->GetAssociatedComponents();
            Selected.insert(AssociatedComponents.begin(), AssociatedComponents.end());
        }
    return Selected;
}

void ApplicationManager::SelectAllComponents()
{
    for(unsigned int i = 0; i < Components.size(); i++)
        Components[i]->SetStatus(SELECTED);
}

void ApplicationManager::ResetComponents()
{
    for(unsigned int i = 0; i < Components.size(); i++)
        Components[i]->Reset();
}

void ApplicationManager::AddComponent(Component* ToBeAdded)
{
    ToBeAdded->GetIn(&SimGrid);
    Components.push_back(ToBeAdded);
}

void ApplicationManager::RemoveComponent(Component* ToBeRemoved)
{
    std::vector<Component*>::iterator dummyIt = std::find(Components.begin(), Components.end(), ToBeRemoved);
    if (dummyIt == Components.end())
        throw "Attempting to remove a component that does NOT exist";
    Components.erase(dummyIt);
    ToBeRemoved->GetOut(&SimGrid);
}

bool ApplicationManager::AreComponentsConnected()
{
    for(unsigned int i = 0; i < Components.size(); i++)
        if (!Components[i]->IsConnected())
            return false;
    return true;
}

bool ApplicationManager::SimulateComponents()
{
	std::vector<bool> IsOperated(Components.size(), false);
	bool Infiniteloop = true;
	do
	{
		for (unsigned int i = 0; i < Components.size(); i++)
			if (!IsOperated[i] && Components[i]->IsReady())
			{
				Infiniteloop = false;
				Components[i]->Operate();
				IsOperated[i] = true;
			}
		if (Infiniteloop)
			return false;
		else
			Infiniteloop = true;
	} while (std::find(IsOperated.begin(), IsOperated.end(), false) != IsOperated.end());
	return true;
}

void ApplicationManager::SaveComponents(std::fstream& File)
{
    for(unsigned int i = 0; i < Components.size(); i++)
        Components[i]->Save(File);
}

void ApplicationManager::CleanUp()
{
    for(unsigned int i = 0; i < Components.size(); i++)
        delete Components[i];
    for(unsigned int i = 0; i < Clipboard.size(); i++)
        delete Clipboard[i];
    for(unsigned int i = 0; i < DoneActions.size(); i++)
        delete DoneActions[i];
    for(unsigned int i = 0; i < UndoneActions.size(); i++)
        delete UndoneActions[i];
    Components.clear();
    Clipboard.clear();
    DoneActions.clear();
    UndoneActions.clear();
    SimGrid.Reset();
}

#pragma once

#include "Enums.h"
#include "Grid.h"
#include "GUI/Interface.h"
#include "Actions/Action.h"

#include <vector>
#include <set>

class Component;
class Pin;

class ApplicationManager
{
private:
    Interface MainInterface;
    std::vector<Action*> DoneActions;
    std::vector<Action*> UndoneActions;
    std::vector<Component*> Clipboard;
    std::vector<Component*> Components;
    Grid SimGrid;

public:
	ApplicationManager();
	~ApplicationManager();

	ActionType GetUserAction();
	void ExecuteAction(ActionType Act);
	void UpdateInterface();
	void SyncInterface();

	Interface* GetInterface();

	void AddCompletedAction(Action* pAction);
	void UndoCompletedAction();
	void RedoUndoneAction();

	bool IsClipboardEmpty() const;
	void PushIntoClipboard(Component* ToBeSaved);
	const std::vector<Component*>& GetClipboard();
	void FlushClipboard();

	std::vector< std::pair<int,int> > FindPathThroughGrid(std::pair<int,int> Point1, std::pair<int,int> Point2);
	bool IsValidCenter(std::pair<int,int> Center) const;
	Component* GetComponentAt(std::pair<int, int> Point);
	Pin* GetPinAt(std::pair<int, int> Point);

    std::vector<SWITCH*> GetSWITCHs();
	std::vector<LED*> GetLEDs();
	std::set<Component*> GetSelectedComponents();
	void SelectAllComponents();
	void ResetComponents();
	void AddComponent(Component* ToBeAdded);
	void RemoveComponent(Component* ToBeRemoved);

	bool AreComponentsConnected();
	bool SimulateComponents();
	void SaveComponents(std::fstream& File);

	void CleanUp();
};

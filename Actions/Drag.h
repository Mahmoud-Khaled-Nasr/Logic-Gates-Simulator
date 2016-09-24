#pragma once

#include "Action.h"

#include <set>
#include <vector>

class Component;
class Connection;

class Drag: public Action
{
private:
    virtual void ReadActionParameters();
    bool IsValid() const;
    void AddComponents();
    void ShiftComponentsBy(std::pair<int,int> Delta);
    void RemoveComponents();
    void AddOutOfRangeConnections();
    void UpdateOutOfRangeConnections();
    void RemoveOutOfRangeConnections();
    void ResetOutOfRangeConnections();
    std::pair<int,int> Delta;
    std::set<Component*> Components;
    std::vector<Connection*> OutOfRangeConnections;
    std::vector< std::vector< std::pair<int,int> > > OldPaths;

public:
    Drag(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

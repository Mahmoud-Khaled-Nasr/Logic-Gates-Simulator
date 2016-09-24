#pragma once

#include <set>
#include <vector>
#include <fstream>

#include "../Enums.h"

class ApplicationManager;
class Grid;
class Interface;
class Pin;

class Component
{
public:
	Component();
	virtual ~Component();
	void SetStatus(ComponentStatus r_Status);
	ComponentStatus GetStatus() const;
	void SetLabel(std::string r_Label);
	std::string GetLabel() const;
	virtual void Reset()=0;
	virtual bool IsConnected() const=0;
	virtual bool IsReady() const=0;
	virtual bool WithinRegion(const std::set<Component*>& Region) const=0;
	virtual std::vector<const Pin*> GetInternalPins() const=0;
	virtual std::set<Component*> GetAssociatedComponents()=0;
	virtual void ShiftBy(std::pair<int,int> Delta)=0;
	virtual std::pair<int,int> GetCenter() const=0;
	virtual void GetIn(Grid* SimGrid)=0;
	virtual void GetOut(Grid* SimGrid)=0;
	virtual void Operate()=0;
	virtual void Draw(Interface* pInterface) const=0;
	virtual void Copy(ApplicationManager* pManager) const=0;
	virtual void Save(std::fstream& File) const=0;

private:
	ComponentStatus m_Status;
	std::string m_Label;
};

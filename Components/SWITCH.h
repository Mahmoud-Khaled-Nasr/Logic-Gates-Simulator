#pragma once

#include "../GraphicsInfo.h"
#include "Component.h"
#include "OutputPin.h"

#include <string>

class SWITCH: public Component
{
public:
    SWITCH(const GraphicsInfo &r_GfxInfo, std::string r_Label="");
	const GraphicsInfo& GetGraphicsInfo() const;
	OutputPin* GetOutputPin();
	void SwitchSignal();
	void SetSignal(Signal r_Signal);
	virtual void Reset();
	virtual bool IsConnected() const;
	virtual bool IsReady() const;
	virtual bool WithinRegion(const std::set<Component*>& Region) const;
	virtual std::vector<const Pin*> GetInternalPins() const;
	virtual std::set<Component*> GetAssociatedComponents();
	virtual void ShiftBy(std::pair<int,int> Delta);
	virtual std::pair<int,int> GetCenter() const;
	virtual void GetIn(Grid* SimGrid);
	virtual void GetOut(Grid* SimGrid);
	virtual void Operate();
	virtual void Draw(Interface* pInterface) const;
	virtual void Copy(ApplicationManager* pManager) const;
	virtual void Save(std::fstream& File) const;

private:
    GraphicsInfo m_GfxInfo;
	OutputPin m_OutputPin;
	Signal m_Signal;
};


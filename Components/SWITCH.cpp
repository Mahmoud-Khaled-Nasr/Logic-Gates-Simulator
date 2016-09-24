#include "SWITCH.h"

#include "../Grid.h"
#include "../ApplicationManager.h"
#include "../GUI/Interface.h"

#include <string>
#include <fstream>
#include <streambuf>
#include <iomanip>

SWITCH::SWITCH(const GraphicsInfo &r_GfxInfo, std::string r_Label): m_GfxInfo(r_GfxInfo), m_OutputPin(std::pair<int,int> (r_GfxInfo.GetX()+10, r_GfxInfo.GetY()+6), 5)
{
    SetLabel(r_Label);
    m_Signal = LOW;
}

const GraphicsInfo& SWITCH::GetGraphicsInfo() const
{
    return m_GfxInfo;
}

OutputPin* SWITCH::GetOutputPin()
{
	return &m_OutputPin;
}

void SWITCH::SwitchSignal()
{
    if (m_Signal == LOW)
    {
        m_Signal = HIGH;
        SetStatus(ON);
    }
    else
    {
        m_Signal = LOW;
        SetStatus(NORMAL);
    }
}

void SWITCH::SetSignal(Signal r_Signal)
{
    m_Signal = r_Signal;
}

void SWITCH::Reset()
{
    SetStatus(NORMAL);
    m_OutputPin.SetStatus(FLOATING);
}

bool SWITCH::IsConnected() const
{
    return m_OutputPin.IsConnected();
}

bool SWITCH::IsReady() const
{
    return true;
}

bool SWITCH::WithinRegion(const std::set<Component*>& Region) const
{
    for(std::set<Component*>::iterator i = Region.begin(); i != Region.end(); i++)
        if ((*i) == this)
            return true;
    return true;
}

std::set<Component*> SWITCH::GetAssociatedComponents()
{
    std::vector<Connection*> dummy = m_OutputPin.GetConnections();
    std::set<Component*> AssociatedComponents;
    for(unsigned int i = 0; i < dummy.size(); i++)
        AssociatedComponents.insert((Component*)(dummy[i]));
    return AssociatedComponents;
}

void SWITCH::ShiftBy(std::pair<int,int> Delta)
{
    m_GfxInfo.ShiftBy(Delta);
    m_OutputPin.ShiftBy(Delta);
}

std::pair<int,int> SWITCH::GetCenter() const
{
    return m_GfxInfo.GetCenter();
}

void SWITCH::GetIn(Grid* SimGrid)
{
    SimGrid->AddSWITCH(this);
}

void SWITCH::GetOut(Grid* SimGrid)
{
    SimGrid->RemoveSWITCH(this);
}

void SWITCH::Operate()
{
    SetStatus((m_Signal == HIGH) ? ON : NORMAL);
    m_OutputPin.SetStatus(m_Signal);
}

void SWITCH::Draw(Interface* pInterface) const
{
    pInterface->DrawComponent(m_GfxInfo, "SWITCH", GetStatus());
    m_OutputPin.Draw(pInterface);
    if (GetStatus() == SELECTED)
        pInterface->DrawLabel(GraphicsInfo(GetGraphicsInfo().GetX(), GetGraphicsInfo().GetY()+GetGraphicsInfo().GetHeight()*2/3, GetGraphicsInfo().GetWidth(), GetGraphicsInfo().GetHeight()/3), GetLabel());
}

void SWITCH::Copy(ApplicationManager* pManager) const
{
    pManager->PushIntoClipboard(new SWITCH(*this));
}

void SWITCH::Save(std::fstream& File) const
{
    File.clear();
    File.seekg(0);
    std::string dummy((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());
    File.clear();
    File.seekp(0);
    File << std::setw(15) << std::left << "SWITCH" << std::setw(5) << std::left << GetGraphicsInfo().GetX() << std::setw(5) << std::left << GetGraphicsInfo().GetY() << std::setw(5) << std::left << GetGraphicsInfo().GetWidth() << std::setw(5) << std::left << GetGraphicsInfo().GetHeight() << GetLabel() << std::endl;
    File << dummy;
}

std::vector<const Pin*> SWITCH::GetInternalPins() const
{
    std::vector<const Pin*> Pins;
    Pins.push_back(&m_OutputPin);
    return Pins;
}

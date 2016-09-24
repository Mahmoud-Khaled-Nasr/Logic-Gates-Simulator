#include "LED.h"

#include "../Grid.h"
#include "../ApplicationManager.h"
#include "../GUI/Interface.h"

#include <string>
#include <fstream>
#include <streambuf>
#include <iomanip>

LED::LED(const GraphicsInfo &r_GfxInfo, std::string r_Label): m_GfxInfo(r_GfxInfo), m_InputPin(std::pair<int,int> (r_GfxInfo.GetX()+2, r_GfxInfo.GetY()+6))
{
    SetLabel(r_Label);
}

const GraphicsInfo& LED::GetGraphicsInfo() const
{
    return m_GfxInfo;
}

InputPin* LED::GetInputPin()
{
	return &m_InputPin;
}

void LED::Reset()
{
    SetStatus(NORMAL);
    m_InputPin.SetStatus(FLOATING);
}

bool LED::IsConnected() const
{
    return m_InputPin.IsConnected();
}

bool LED::IsReady() const
{
    return m_InputPin.GetStatus() != FLOATING;
}

bool LED::WithinRegion(const std::set<Component*>& Region) const
{
    for(std::set<Component*>::iterator i = Region.begin(); i != Region.end(); i++)
        if ((*i) == this)
            return true;
    return true;
}

std::set<Component*> LED::GetAssociatedComponents()
{
    std::set<Component*> AssociatedComponents;
    if (m_InputPin.IsConnected())
        AssociatedComponents.insert((Component*)m_InputPin.GetConnection());
    return AssociatedComponents;
}

void LED::ShiftBy(std::pair<int,int> Delta)
{
    m_GfxInfo.ShiftBy(Delta);
    m_InputPin.ShiftBy(Delta);
}

std::pair<int,int> LED::GetCenter() const
{
    return m_GfxInfo.GetCenter();
}

void LED::GetIn(Grid* SimGrid)
{
    SimGrid->AddLED(this);
}

void LED::GetOut(Grid* SimGrid)
{
    SimGrid->RemoveLED(this);
}

void LED::Operate()
{
    if (m_InputPin.GetStatus() == HIGH)
        SetStatus(ON);
    else
        SetStatus(NORMAL);
}

void LED::Draw(Interface* pInterface) const
{
    pInterface->DrawComponent(m_GfxInfo, "LED", GetStatus());
    m_InputPin.Draw(pInterface);
    if (GetStatus() == SELECTED)
        pInterface->DrawLabel(GraphicsInfo(GetGraphicsInfo().GetX(), GetGraphicsInfo().GetY()+GetGraphicsInfo().GetHeight()*2/3, GetGraphicsInfo().GetWidth(), GetGraphicsInfo().GetHeight()/3), GetLabel());
}

void LED::Copy(ApplicationManager* pManager) const
{
    pManager->PushIntoClipboard(new LED(*this));
}

void LED::Save(std::fstream& File) const
{
    File.clear();
    File.seekg(0);
    std::string dummy((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());
    File.clear();
    File.seekp(0);
    File << std::setw(15) << std::left << "LED" << std::setw(5) << std::left << GetGraphicsInfo().GetX() << std::setw(5) << std::left << GetGraphicsInfo().GetY() << std::setw(5) << std::left << GetGraphicsInfo().GetWidth() << std::setw(5) << std::left << GetGraphicsInfo().GetHeight() << GetLabel() << std::endl;
    File << dummy;
}

std::vector<const Pin*> LED::GetInternalPins() const
{
    std::vector<const Pin*> Pins;
    Pins.push_back(&m_InputPin);
    return Pins;
}

#include "Gate.h"

#include "InputPin.h"
#include "../Grid.h"

Gate::Gate(const GraphicsInfo &r_GfxInfo, int r_FanOut): m_GfxInfo(r_GfxInfo), m_OutputPin(std::pair<int,int> (r_GfxInfo.GetX()+10, r_GfxInfo.GetY()+6), r_FanOut) {}

const GraphicsInfo& Gate::GetGraphicsInfo() const
{
    return m_GfxInfo;
}

std::vector<InputPin>& Gate::GetInputPins()
{
    return m_InputPins;
}

OutputPin* Gate::GetOutputPin()
{
    return &m_OutputPin;
}

void Gate::Reset()
{
    SetStatus(NORMAL);
    m_OutputPin.SetStatus(FLOATING);
    for(unsigned int i = 0; i < m_InputPins.size(); i++)
        m_InputPins[i].SetStatus(FLOATING);
}

bool Gate::IsConnected() const
{
    if (!m_OutputPin.IsConnected())
        return false;
    for(unsigned int i = 0; i < m_InputPins.size(); i++)
        if (!m_InputPins[i].IsConnected())
            return false;
    return true;
}

bool Gate::IsReady() const
{
    for(unsigned int i = 0; i < m_InputPins.size(); i++)
        if (m_InputPins[i].GetStatus() == FLOATING)
            return false;
    return true;
}

bool Gate::WithinRegion(const std::set<Component*>& Region) const
{
    for(std::set<Component*>::iterator i = Region.begin(); i != Region.end(); i++)
        if ((*i) == this)
            return true;
    return true;
}

std::set<Component*> Gate::GetAssociatedComponents()
{
    std::vector<Connection*> dummy = m_OutputPin.GetConnections();
    std::set<Component*> AssociatedComponents;
    for(unsigned int i = 0; i < dummy.size(); i++)
        AssociatedComponents.insert((Component*)(dummy[i]));
    for(unsigned int i = 0; i < m_InputPins.size(); i++)
        if (m_InputPins[i].IsConnected())
            AssociatedComponents.insert((Component*)(m_InputPins[i].GetConnection()));
    return AssociatedComponents;
}

void Gate::ShiftBy(std::pair<int,int> Delta)
{
    m_GfxInfo.ShiftBy(Delta);
    for(unsigned int i = 0; i < m_InputPins.size(); i++)
        m_InputPins[i].ShiftBy(Delta);
    m_OutputPin.ShiftBy(Delta);
}

std::pair<int,int> Gate::GetCenter() const
{
    return m_GfxInfo.GetCenter();
}

void Gate::GetIn(Grid* SimGrid)
{
    SimGrid->AddGate(this);
}

void Gate::GetOut(Grid* SimGrid)
{
    SimGrid->RemoveGate(this);
}

std::vector<const Pin*> Gate::GetInternalPins() const
{
    std::vector<const Pin*> Pins;
    Pins.push_back(&m_OutputPin);
    for(unsigned int i = 0; i < m_InputPins.size(); i++)
        Pins.push_back(&(m_InputPins[i]));
    return Pins;
}

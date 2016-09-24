#include "Connection.h"

#include "../ApplicationManager.h"
#include "../Grid.h"
#include "Pin.h"
#include "Interface.h"

#include <fstream>
#include <iomanip>

Connection::Connection(Pin* r_InputPin, Pin* r_OutputPin, const std::vector< std::pair<int,int> >& r_Vertices, std::string r_Label)
{
    m_InputPin = r_InputPin;
    m_OutputPin = r_OutputPin;
    m_Vertices = r_Vertices;
    SetLabel(r_Label);
}

void Connection::Update(const std::vector< std::pair<int,int> >& r_Vertices)
{
    m_Vertices = r_Vertices;
}

const std::vector< std::pair<int,int> >& Connection::GetPath()
{
    return m_Vertices;
}

std::pair< std::pair<int,int> , std::pair<int,int> > Connection::GetPinsCoordinates()
{
    return std::pair< std::pair<int,int> , std::pair<int,int> > (m_InputPin->GetCenter(), m_OutputPin->GetCenter());
}

void Connection::Reset()
{
    SetStatus(NORMAL);
}

bool Connection::IsConnected() const
{
    return m_InputPin->IsConnected() && m_OutputPin->IsConnected();
}

bool Connection::IsReady() const
{
    return m_InputPin->GetStatus() != FLOATING;
}

bool Connection::WithinRegion(const std::set<Component*>& Region) const
{
    std::set<const Pin*> Pins;
    for(std::set<Component*>::iterator i = Region.begin(); i != Region.end(); i++)
    {
        std::vector<const Pin*> dummy = (*i)->GetInternalPins();
        Pins.insert(dummy.begin(), dummy.end());
    }
    return Pins.find(m_InputPin) != Pins.end() && Pins.find(m_OutputPin) != Pins.end();
}

std::set<Component*> Connection::GetAssociatedComponents()
{
    std::set<Component*> dummy;
    return dummy;
}

void Connection::ShiftBy(std::pair<int,int> Delta)
{
    for(unsigned int i = 0; i < m_Vertices.size(); i++)
    {
        m_Vertices[i].first += Delta.first;
        m_Vertices[i].second += Delta.second;
    }
}

std::pair<int,int> Connection::GetCenter() const
{
    return std::pair<int,int> ((m_Vertices.front().first+m_Vertices.back().first)/2, (m_Vertices.front().second+m_Vertices.back().second)/2);
}

void Connection::GetIn(Grid* SimGrid)
{
    SimGrid->AddConnection(this);
    m_InputPin->ConnectTo(this);
    m_OutputPin->ConnectTo(this);
}

void Connection::GetOut(Grid* SimGrid)
{
    SimGrid->RemoveConnection(this);
    m_InputPin->DeconnectFrom(this);
    m_OutputPin->DeconnectFrom(this);
}

void Connection::Operate()
{
    m_OutputPin->SetStatus(m_InputPin->GetStatus());
}

void Connection::Draw(Interface* pInterface) const
{
    pInterface->DrawConnection(m_Vertices, GetStatus(), m_InputPin->GetStatus());
    m_InputPin->Draw(pInterface);
    m_OutputPin->Draw(pInterface);
}

void Connection::Copy(ApplicationManager* pManager) const
{
    return;
}

void Connection::Save(std::fstream& File) const
{
    for(unsigned int i = 0; i < m_Vertices.size(); i++)
        File << std::setw(5) << std::left << m_Vertices[i].first << std::setw(5) << m_Vertices[i].second;
    File << std::endl;
}

std::vector<const Pin*> Connection::GetInternalPins() const
{
    std::vector<const Pin*> Pins;
    return Pins;
}

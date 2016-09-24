#include "OutputPin.h"

#include "../GUI/Interface.h"

OutputPin::OutputPin(std::pair<int,int> r_Center, int r_FanOut): Pin(r_Center)
{
	m_FanOut = r_FanOut;
}

OutputPin::OutputPin(const OutputPin& Original): Pin(Original)
{
    m_FanOut = Original.m_FanOut;
    m_Connections.clear();
}

std::vector<Connection*> OutputPin::GetConnections()
{
    return m_Connections;
}

bool OutputPin::IsConnected() const
{
    return !m_Connections.empty();
}

bool OutputPin::IsConnectable() const
{
    return (int)m_Connections.size() < m_FanOut;
}

void OutputPin::ConnectTo(Connection * r_Connection)
{
	if ((int)m_Connections.size() == m_FanOut)
        throw "Attempting to connect a fully-connected pin";
	m_Connections.push_back(r_Connection);
}

void OutputPin::DeconnectFrom(Connection * r_Connection)
{
	std::vector<Connection*>::iterator dummyIt = std::find(m_Connections.begin(), m_Connections.end(), r_Connection);
    if (dummyIt == m_Connections.end())
        throw "Attempting to deconnect a pin from a connection that is not connected to";
    m_Connections.erase(dummyIt);
}

void OutputPin::Draw(Interface* pInterface) const
{
    pInterface->DrawPin(GetCenter(), m_Connections.size() != 0, IsConnectable());
}

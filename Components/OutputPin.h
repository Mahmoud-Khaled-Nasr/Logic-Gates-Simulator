#pragma once

#include "Pin.h"

#include <vector>

class Connection;

class OutputPin: public Pin
{
private:
	int m_FanOut;
	std::vector<Connection*> m_Connections;

public:
	OutputPin(std::pair<int,int> r_Center, int r_FanOut);
	OutputPin(const OutputPin& Original);
	std::vector<Connection*> GetConnections();
	virtual bool IsConnected() const;
	virtual bool IsConnectable() const;
	virtual void ConnectTo(Connection* r_Connection);
	virtual void DeconnectFrom(Connection* r_Connection);
	virtual void Draw(Interface* pInterface) const;
};

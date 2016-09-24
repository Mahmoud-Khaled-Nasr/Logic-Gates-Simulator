#pragma once

#include "Pin.h"

class Connection;

class InputPin: public Pin
{
private:
	Connection* m_Connection;

public:
	InputPin(std::pair<int,int> r_Center);
	InputPin(const InputPin& Original);
	Connection* GetConnection();
	virtual bool IsConnected() const;
	virtual bool IsConnectable() const;
	virtual void ConnectTo(Connection* r_Connection);
	virtual void DeconnectFrom(Connection* r_Connection);
	virtual void Draw(Interface* pInterface) const;
};

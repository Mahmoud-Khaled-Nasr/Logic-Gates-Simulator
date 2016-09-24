#pragma once

#include <utility>

#include "../Enums.h"

class Connection;
class Interface;

class Pin
{
private:
    std::pair<int,int> m_Center;
    Signal m_Status;

public:
	Pin(std::pair<int,int> r_Center);
	virtual ~Pin();
	void SetCenter(std::pair<int,int> r_Center);
	std::pair<int,int> GetCenter() const;
	void ShiftBy(std::pair<int,int> Delta);
	void SetStatus(Signal r_Status);
	Signal GetStatus() const;
	virtual bool IsConnected() const=0;
	virtual bool IsConnectable() const=0;
	virtual void ConnectTo(Connection* r_Connection)=0;
	virtual void DeconnectFrom(Connection* r_Connection)=0;
	virtual void Draw(Interface* pInterface) const=0;
};

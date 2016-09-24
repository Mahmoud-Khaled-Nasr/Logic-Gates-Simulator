#include "Pin.h"

Pin::Pin(std::pair<int,int> r_Center): m_Center(r_Center)
{
	SetStatus(FLOATING);
}

Pin::~Pin() {}

void Pin::SetCenter(std::pair<int,int> r_Center)
{
    m_Center = r_Center;
}

std::pair<int,int> Pin::GetCenter() const
{
    return m_Center;
}

void Pin::ShiftBy(std::pair<int,int> Delta)
{
    m_Center.first += Delta.first;
    m_Center.second += Delta.second;
}

void Pin::SetStatus(Signal r_Status)
{
    m_Status = r_Status;
}

Signal Pin::GetStatus() const
{
    return m_Status;
}

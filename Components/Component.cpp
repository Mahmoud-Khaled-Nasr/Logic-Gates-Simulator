#include "Component.h"

Component::Component()
{
    SetStatus(NORMAL);
}

Component::~Component() {}

void Component::SetStatus(ComponentStatus r_Status)
{
    m_Status = r_Status;
}

ComponentStatus Component::GetStatus() const
{
    return m_Status;
}

void Component::SetLabel(std::string r_Label)
{
    if (r_Label != "")
        m_Label = r_Label;
}

std::string Component::GetLabel() const
{
    if (m_Label == "")
        return "$";
    return m_Label;
}

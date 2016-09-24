#pragma once

#include "../Enums.h"
#include "../GraphicsInfo.h"
#include "Interface.h"

#include <string>

class Output;

class Button
{
public:
    Button(const GraphicsInfo& r_GfxInfo, const std::string& r_ImagePath, ActionType r_ActionType, Interface::ButtonStatus r_Status);
    ~Button();
    void Draw(Output* pOut);
    void SetStatus(Interface::ButtonStatus r_Status);
    Interface::ButtonStatus GetStatus() const;
    ActionType GetAction() const;
    const GraphicsInfo& GetGraphicsInfo() const;

private:
    GraphicsInfo m_GfxInfo;
    std::string m_ImagePath;
    ActionType m_ActionType;
    Interface::ButtonStatus m_Status;
    friend class Bar;
};

#pragma once

#include "../GraphicsInfo.h"
#include "Button.h"

#include <string>
#include <vector>

class Output;

class Bar
{
public:
    enum BarLayout {VERTICAL, HORIZONTAL};
    Bar(const GraphicsInfo& r_GfxInfo, BarLayout r_Layout, int r_Spacing);
    ~Bar();
    void Draw(Output* pOut);
    void AddButton(const std::string& ImagePath, ActionType Act, Interface::ButtonStatus Status = Interface::NORMAL, int Offset = 0);
    void OptimizeSpacing();
    const GraphicsInfo& GetGraphicsInfo() const;
    const std::vector<Button*>& GetButtons() const;
private:
    GraphicsInfo m_GfxInfo;
    BarLayout m_Layout;
    int m_Spacing;
    bool Optimized;
    std::vector<Button*> Buttons;
};

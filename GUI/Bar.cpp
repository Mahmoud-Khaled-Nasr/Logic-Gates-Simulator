#include "Bar.h"

#include "Output.h"

Bar::Bar(const GraphicsInfo& r_GfxInfo, BarLayout r_Layout, int r_Spacing): m_GfxInfo(r_GfxInfo)
{
    m_Layout = r_Layout;
    m_Spacing = r_Spacing;
    Optimized = false;
}

Bar::~Bar()
{
    for(unsigned int i = 0; i < Buttons.size(); i++)
        if (Buttons[i] != NULL)
            delete Buttons[i];
}

void Bar::Draw(Output* pOut)
{
    pOut->DrawBar(m_GfxInfo);
    for(unsigned int i = 0; i < Buttons.size(); i++)
        if (Buttons[i] != NULL)
            Buttons[i]->Draw(pOut);
}

void Bar::AddButton(const std::string& ImagePath, ActionType r_ActionType, Interface::ButtonStatus Status, int Offset)
{
    if (Optimized)
        return;
    for(int i = 0; i < Offset; i++)
        Buttons.push_back(NULL);
    int X, Y, Width, Height;
    switch (m_Layout)
    {
    case VERTICAL:
        X = m_GfxInfo.GetX() + m_Spacing;
        Y = m_GfxInfo.GetY() + Buttons.size()*(m_GfxInfo.GetWidth()-m_Spacing) + m_Spacing;
        Width = m_GfxInfo.GetWidth() - 2*m_Spacing;
        Height = Width;
        break;
    case HORIZONTAL:
        X = m_GfxInfo.GetX() + Buttons.size()*(m_GfxInfo.GetHeight()-m_Spacing) + m_Spacing;
        Y = m_GfxInfo.GetY() + m_Spacing;
        Height = m_GfxInfo.GetHeight() - 2*m_Spacing;
        Width = Height;
        break;
    }
    Buttons.push_back(new Button(GraphicsInfo(X, Y, Width, Height), ImagePath, r_ActionType, Status));
}

void Bar::OptimizeSpacing()
{
    switch (m_Layout)
    {
    case VERTICAL:
        m_Spacing = (m_GfxInfo.GetHeight()-(m_GfxInfo.GetWidth()-2*m_Spacing)*Buttons.size())/(1+Buttons.size());
        for(unsigned int i = 0; i < Buttons.size(); i++)
            if (Buttons[i] != NULL)
                Buttons[i]->m_GfxInfo.SetY(m_GfxInfo.GetY()+m_Spacing+i*(m_Spacing+Buttons[i]->m_GfxInfo.GetHeight()));
        break;
    case HORIZONTAL:
        m_Spacing = (m_GfxInfo.GetWidth()-(m_GfxInfo.GetHeight()-2*m_Spacing)*Buttons.size())/(1+Buttons.size());
        for(unsigned int i = 0; i < Buttons.size(); i++)
            if (Buttons[i] != NULL)
                Buttons[i]->m_GfxInfo.SetX(m_GfxInfo.GetX()+m_Spacing+i*(m_Spacing+Buttons[i]->m_GfxInfo.GetWidth()));
        break;
    }
    Optimized = true;
}

const GraphicsInfo& Bar::GetGraphicsInfo() const
{
    return m_GfxInfo;
}

const std::vector<Button*>& Bar::GetButtons() const
{
    return Buttons;
}

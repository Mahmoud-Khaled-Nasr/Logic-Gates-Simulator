#include "Canvas.h"

#include "Output.h"

Canvas::Canvas(const GraphicsInfo& r_GfxInfo): m_GfxInfo(r_GfxInfo)
{
    m_ShowGrid = true;
}

Canvas::~Canvas() {}

void Canvas::Draw(Output* pOut)
{
    pOut->DrawCanvas(m_GfxInfo, m_ShowGrid);
}

void Canvas::SetGridStatus(bool Shown)
{
    m_ShowGrid = Shown;
}

const GraphicsInfo& Canvas::GetGraphicsInfo() const
{
    return m_GfxInfo;
}

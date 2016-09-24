#pragma once

#include "../GraphicsInfo.h"

class Output;

class Canvas
{
public:
    Canvas(const GraphicsInfo& r_GfxInfo);
    ~Canvas();
    void Draw(Output* pOut);
    void SetGridStatus(bool Shown);
    const GraphicsInfo& GetGraphicsInfo() const;

private:
    GraphicsInfo m_GfxInfo;
    bool m_ShowGrid;
};

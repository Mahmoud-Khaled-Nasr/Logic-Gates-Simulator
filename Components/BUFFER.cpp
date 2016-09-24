#include "BUFFER.h"

#include "../ApplicationManager.h"
#include "../GUI/Interface.h"

#include <string>
#include <fstream>
#include <streambuf>
#include <iomanip>

BUFFER::BUFFER(const GraphicsInfo & r_GfxInfo, std::string r_Label): Gate(r_GfxInfo, 5)
{
	m_InputPins.push_back(InputPin(std::pair<int,int> (r_GfxInfo.GetX()+2, r_GfxInfo.GetY()+6)));
	SetLabel(r_Label);
}

void BUFFER::Operate()
{
    m_OutputPin.SetStatus(m_InputPins[0].GetStatus());
}

void BUFFER::Draw(Interface* pInterface) const
{
	pInterface->DrawComponent(GetGraphicsInfo(), "BUFFER", GetStatus());
	for(unsigned int i = 0; i < m_InputPins.size(); i++)
        m_InputPins[i].Draw(pInterface);
    m_OutputPin.Draw(pInterface);
    if (GetStatus() == SELECTED)
        pInterface->DrawLabel(GraphicsInfo(GetGraphicsInfo().GetX(), GetGraphicsInfo().GetY()+GetGraphicsInfo().GetHeight()*2/3, GetGraphicsInfo().GetWidth(), GetGraphicsInfo().GetHeight()/3), GetLabel());
}

void BUFFER::Copy(ApplicationManager * pManager) const
{
	pManager->PushIntoClipboard(new BUFFER(*this));
}

void BUFFER::Save(std::fstream& File) const
{
    File.clear();
    File.seekg(0);
    std::string dummy((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());
    File.clear();
    File.seekp(0);
    File << std::setw(15) << std::left << "BUFFER" << std::setw(5) << std::left << GetGraphicsInfo().GetX() << std::setw(5) << std::left << GetGraphicsInfo().GetY() << std::setw(5) << std::left << GetGraphicsInfo().GetWidth() << std::setw(5) << std::left << GetGraphicsInfo().GetHeight() << GetLabel() << std::endl;
    File << dummy;
}

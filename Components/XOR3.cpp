#include "XOR3.h"

#include "../ApplicationManager.h"
#include "../GUI/Interface.h"

#include <string>
#include <fstream>
#include <streambuf>
#include <iomanip>

XOR3::XOR3(const GraphicsInfo & r_GfxInfo, std::string r_Label) : Gate(r_GfxInfo, 5)
{
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 5)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 6)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 7)));
	SetLabel(r_Label);
}

void XOR3::Operate()
{
	int Count = 0;
	for (unsigned int  i = 0; i < m_InputPins.size(); i++)
		if (m_InputPins[i].GetStatus() == HIGH)
			Count++;
	if (Count%2 == 1)
		m_OutputPin.SetStatus(HIGH);
	else
		m_OutputPin.SetStatus(LOW);
}

void XOR3::Draw(Interface * pInterface) const
{
	pInterface->DrawComponent(GetGraphicsInfo(), "XOR3", GetStatus());
	for (unsigned int i = 0; i < m_InputPins.size(); i++)
		m_InputPins[i].Draw(pInterface);
	m_OutputPin.Draw(pInterface);
    if (GetStatus() == SELECTED)
        pInterface->DrawLabel(GraphicsInfo(GetGraphicsInfo().GetX(), GetGraphicsInfo().GetY()+GetGraphicsInfo().GetHeight()*2/3, GetGraphicsInfo().GetWidth(), GetGraphicsInfo().GetHeight()/3), GetLabel());
}

void XOR3::Copy(ApplicationManager * pManager) const
{
	pManager->PushIntoClipboard(new XOR3(*this));
}

void XOR3::Save(std::fstream& File) const
{
    File.clear();
    File.seekg(0);
    std::string dummy((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());
    File.clear();
    File.seekp(0);
    File << std::setw(15) << std::left << "XOR3" << std::setw(5) << std::left << GetGraphicsInfo().GetX() << std::setw(5) << std::left << GetGraphicsInfo().GetY() << std::setw(5) << std::left << GetGraphicsInfo().GetWidth() << std::setw(5) << std::left << GetGraphicsInfo().GetHeight() << GetLabel() << std::endl;
    File << dummy;
}

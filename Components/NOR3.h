#pragma once

#include "Gate.h"

class NOR3 : public Gate
{
public:
	NOR3(const GraphicsInfo &r_GfxInfo, std::string r_Label = "");
	virtual void Operate();
	virtual void Draw(Interface* pInterface) const;
	virtual void Copy(ApplicationManager* pManager) const;
	virtual void Save(std::fstream& File) const;
};


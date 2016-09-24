#pragma once

#include "../Enums.h"
#include "../GraphicsInfo.h"
#include "Interface.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Interface;

class Output
{
private:
	Interface* pInterface;
	Interface::MouseStatus m_MouseStatus;
	std::string TooltipText;
	void DrawImage(const GraphicsInfo& GfxInfo, std::string ImagePath);
	void DrawRectangle(const GraphicsInfo& GfxInfo, sf::Color Color, int Thickness=0, sf::Color OutlineColor=sf::Color::Transparent);
	void DrawText(const GraphicsInfo& GfxInfo, std::string Text, std::string FontPath);
	void DrawTooltip();
	void HandleMouse();

public:
	Output(Interface* pInterface);
	void DrawBar(const GraphicsInfo& GfxInfo);
	void DrawButton(const GraphicsInfo& GfxInfo, std::string ImagePath, Interface::ButtonStatus Status);
	void DrawCanvas(const GraphicsInfo& GfxInfo, bool ShowGrid = true);
	void DrawComponent(const GraphicsInfo& GfxInfo, std::string ImagePath, ComponentStatus r_Status);
	void DrawLabel(const GraphicsInfo& GfxInfo, std::string Text, std::string Font);
	void DrawPin(std::pair<int,int> Center, bool Connected, bool Connectable, std::string ImagePath);
	void DrawConnection(const std::vector< std::pair<int,int> >& Vertices, ComponentStatus r_Status, Signal r_Signal);
	void DrawSelectionRectangle(const GraphicsInfo& GfxInfo);
	void SetTooltipText(std::string Text);
	void SetMouseStatus(Interface::MouseStatus r_MouseStatus);
	void DrawBorders();
	void SyncWindow();
};

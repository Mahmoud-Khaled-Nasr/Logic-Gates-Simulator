#pragma once

#include "../Enums.h"

#include <SFML/Graphics.hpp>

class Interface;
class Output;
class Bar;
class Button;

class Input
{
private:
	Interface* pInterface;

public:
	Input(Interface* pInterface);
	~Input();
	std::pair<int,int> GetMousePosition() const;
	std::pair<int,int> GetPointClicked() const;
	std::pair<int,int> GetInstantClick() const;
	std::pair<int,int> GetInstantRelease() const;
	std::string GetSrting() const;
	ActionType GetUserAction() const;
	bool IsSingleClick() const;
	bool IsDoubleClick() const;
	bool IsDragging() const;
	bool IsCtrlOn() const;
};

#pragma once
#include "UIComponent.h"
class UIRadioButton :
	public UIComponent
{
private:
	unordered_map<int, bool> opt_; // = unordered_map<int, bool>().clear();
public:
	UIRadioButton() {};
	virtual ~UIRadioButton() {};
};


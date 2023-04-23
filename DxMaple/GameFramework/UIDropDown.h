#pragma once
#include "UIComponent.h"
#include "UILabel.h"

class UIDropDown :
	public UIComponent
{
private:
	unordered_map< int, weak_ptr<UILabel>> list_;

public:
	UIDropDown() {};
	virtual ~UIDropDown() {};
};


#pragma once
#include "UIComponent.h"
#include "DXFont.h"

class UILabel :
	public UIComponent
{
private:
	weak_ptr<string> text_;
	bool multiLine_;
//	DXFont
public:
	UILabel() {};
	virtual ~UILabel() {};
};


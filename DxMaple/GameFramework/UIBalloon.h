#pragma once
#include "UIComponent.h"

#include "UILabel.h"
#include "UIWindow.h"

typedef tuple<UILabel, UIWindow> Balloon;

class UIBalloon :
	public UIComponent
{
private:
	Balloon balloon_;
public:
	UIBalloon() {};
	virtual ~UIBalloon() {};
};


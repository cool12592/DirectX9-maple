#pragma once
#include "UIComponent.h"


class UIWindow : public UIComponent
{
private:
	RECT textRT;
	_vec2 pos_;
public:
	UIWindow() { } ;
	virtual ~UIWindow() { };


	void setWindow(wstring bufferName, wstring shaderName, wstring Name, wstring AtlasName, wstring JsonName, float x, float y);
	void setFont(string fontName, int fontSize, wstring text, D3DXCOLOR col, int x, int y);
	void initialize();
	void update();
	void lateUpdate();
	void render();
	void release();

};


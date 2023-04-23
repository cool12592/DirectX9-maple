#pragma once
#include "UIComponent.h"

class UIButton :
	public UIComponent
{

public:
	UIButton() {};
	virtual ~UIButton() {};
public:
	void initialize();
	bool OnMouse();
	bool OnClick();
	bool OnIdle();
	void update();
	void lateUpdate();
	void render();
	void release();
	void setWindow(wstring bufferName, wstring shaderName, wstring Name, wstring AtalasName, wstring JsonName);
	void open(float x, float y);
	void setWindow(wstring bufferName, wstring shaderName, wstring Name, wstring AtalasName, wstring JsonName, float x, float y);

	void setIdle(wstring Atalasname, int index);
	void setOn(wstring Atalasname, int index);
	void setClick(wstring Atalasname, int index);
	void setOff(wstring Atalasname, int index);
	void setMove(float x, float y) { entity->getComponent<Transform>().position_.x += x; entity->getComponent<Transform>().position_.y += y; }
	void setSize(float x, float y) { entity->getComponent<Transform>().scale_.x *= x; entity->getComponent<Transform>().scale_.y *= y; }

};


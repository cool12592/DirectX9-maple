#include "stdafx.h"
#include "UIComponent.h"

USING(UIState)
Idle Idle::instance;
Move Move::instance;
//UIState::Timer UIState::Timer::instance;
Left Left::instance;
Right Right::instance;
On On::instance;
Off Off::instance;

UIComponent::UIComponent() {}
UIComponent::~UIComponent()
{

}
void UIComponent::setFont(string fontName, int fontSize, int x, int y, wstring text, D3DXCOLOR col)
{
	RECT rt;
	rt.left = x;
	rt.top = y;
	rt.right = -rt.left + SCREEN_WIDTH;
	rt.bottom = -rt.top + SCREEN_HEIGHT;
	entity->getComponent<DXFont>().SetScript(fontName.c_str(), fontSize, FW_NORMAL, rt, text.c_str(), col);

}

void UIComponent::initialize() 
{
	DeviceManager::getInstance()->getScreenSize(screenWidth_, screenHeight_);

	//entity->addComponent<Transform>(_vec3(0,0,-90),_vec3(0,0,0),_vec3(1,1,0));
	entity->addComponent<DXFont>();


}


void UIComponent::update()
{
 }
void UIComponent::lateUpdate()
{

 }
void UIComponent::render()
{
 }
void UIComponent::release()
{

 }

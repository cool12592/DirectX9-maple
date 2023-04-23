#include "stdafx.h"
#include "UIWindow.h"
//#include "UIText.h"


void UIWindow::setWindow(wstring bufferName, wstring shaderName, wstring Name, wstring AtlasName, wstring JsonName,float x,float y)
{
	entity->addComponent<AtlasAnimation>(bufferName, shaderName);
	entity->getComponent<AtlasAnimation>().insertSprite(Name, AtlasName.c_str(), JsonName.c_str());
	_vec2 Atlaspos = entity->getComponent<AtlasAnimation>().getAltInfo();

	entity->getComponent<Transform>().position_.x += (float)((-SCREEN_WIDTH / 2) + (Atlaspos.x/2)+x);
	entity->getComponent<Transform>().position_.y += (float)((+SCREEN_HEIGHT / 2) - (Atlaspos.y / 2) - y);

	entity->getComponent<AtlasAnimation>().isZRender = false;
	entity->addComponent<DXFont>();


}
void UIWindow::setFont(string fontName, int fontSize, wstring text, D3DXCOLOR col, int x, int y)
{
	_vec2 Atlaspos = entity->getComponent<AtlasAnimation>().getAltInfo();

	textRT.left = (LONG)(pos_.x + x);
	textRT.top = (LONG)(pos_.y + y);
	textRT.right = (LONG)(textRT.left + Atlaspos.x);
	textRT.bottom = (LONG)(textRT.top + Atlaspos.y);
	entity->getComponent<DXFont>().SetScript(fontName.c_str(), fontSize, FW_NORMAL, textRT, text.c_str(), col);

}

void UIWindow::initialize()
{
	__super::initialize();

}
void UIWindow::update()
{
	int x, y;
	Input.getMousePosition(x, y);
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "Player Controller need transform component");
	Transform& transform = entity->getComponent<Transform>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();

	//Sound& sound = entity->getComponent<Sound>();
	//fighter_tigerstriker& tigerstriker = entity->getComponent<fighter_tigerstriker>();

	commandInput(x, y);


	//충돌계산.
	OnMove();
	OnIdle();
	OnClick();
}
void UIWindow::lateUpdate()
{

}
void UIWindow::render()
{
}
void UIWindow::release()
{

}

//void UIWindow::OnMouse()
//{
//	StateMachine& stateMachine = entity->getComponent<StateMachine>();
//	stateMachine.changeState(L"on");
//}
//void UIWindow::OnIdle()
//{
//	StateMachine& stateMachine = entity->getComponent<StateMachine>();
//	stateMachine.changeState(L"idle");
//	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "Controller need transform component");
//	if (Input.mouseDown(InputManager::MOUSEBUTTONTYPE::LEFT))
//		stateMachine.transitionState(UIState::Transition::CLICK);
//	else if (Input.mouseDown(InputManager::MOUSEBUTTONTYPE::RIGHT))
//		stateMachine.transitionState(UIState::Transition::RIGHT);
//	else
//		stateMachine.transitionState(UIState::Transition::MOVE);
//
//}

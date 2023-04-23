#include "stdafx.h"
#include "UIButton.h"

void UIButton::setWindow(wstring bufferName, wstring shaderName, wstring Name, wstring AtalasName, wstring JsonName)
{
	entity->addComponent<AtlasAnimation>(bufferName, shaderName);
	entity->getComponent<AtlasAnimation>().insertSprite(Name.c_str(), AtalasName.c_str(), JsonName.c_str());
	Transform& trans = entity->getComponent<Transform>();
	//trans.position_.x = -999.f;
	//trans.position_.y = -999.f;
	entity->getComponent<AtlasAnimation>().isZRender = false;
}
void UIButton::open(float x, float y)
{
		AtlasAnimation& Anim = entity->getComponent<AtlasAnimation>();
		_vec2 Atlaspos = Anim.getAltInfo();
		Transform& trans = entity->getComponent<Transform>();
		trans.position_.x = (float)((-SCREEN_WIDTH / 2) + (Atlaspos.x / 2) + x);
		trans.position_.y = (float)((+SCREEN_HEIGHT / 2) - (Atlaspos.y / 2) - y);
		entity->addComponent<Ray>();
		entity->addComponent<BoxCollider>(_vec3(trans.position_.x, trans.position_.y, 0), _vec3(0, 0, 0), _vec3(Atlaspos.x, Atlaspos.y, 1));

}
void UIButton::setWindow(wstring bufferName, wstring shaderName, wstring Name, wstring AtalasName, wstring JsonName, float x, float y)
{


	entity->addComponent<AtlasAnimation>(bufferName, shaderName);
	entity->getComponent<AtlasAnimation>().insertSprite(AtalasName.c_str(), AtalasName.c_str(), JsonName.c_str());
	AtlasAnimation& Anim = entity->getComponent<AtlasAnimation>();
	_vec2 Atlaspos = Anim.getAltInfo();


	entity->getComponent<AtlasAnimation>().setAddPos(_vec3(
		(float)((-SCREEN_WIDTH / 2) + (Atlaspos.x / 2) + x),
		(float)((+SCREEN_HEIGHT / 2) - (Atlaspos.y / 2) - y),
		0));
	
	//pos_ = Atlaspos;
	Transform& trans = entity->getComponent<Transform>();
	trans.position_.x = (float)((-SCREEN_WIDTH / 2) + (Atlaspos.x / 2) + x),
		(float)((+SCREEN_HEIGHT / 2) - (Atlaspos.y / 2) - y);

	trans.position_.y = (float)((-SCREEN_WIDTH / 2) + (Atlaspos.x / 2) + x),
		(float)((+SCREEN_HEIGHT / 2) - (Atlaspos.y / 2) - y);
;

	entity->addComponent<Ray>();
	entity->addComponent<BoxCollider>(_vec3(trans.position_.x, trans.position_.y,0),_vec3(0,0,0),_vec3(Atlaspos.x, Atlaspos.y,1));
	entity->getComponent<AtlasAnimation>().isZRender = false;


}
void UIButton::setIdle(wstring Atalasname, int index)
{
	AtlasAnimation& Anim = entity->getComponent<AtlasAnimation>();
	Anim.insertMotionData(Atalasname, L"idle", index, index);
}
void UIButton::setOn(wstring Atalasname, int index)
{
	AtlasAnimation& Anim = entity->getComponent<AtlasAnimation>();
	Anim.insertMotionData(Atalasname, L"on", index, index);
}
void UIButton::setClick(wstring Atalasname, int index)
{
	AtlasAnimation& Anim = entity->getComponent<AtlasAnimation>();
	Anim.insertMotionData(Atalasname, L"left", index, index);
}
void UIButton::setOff(wstring Atalasname, int index)
{
	AtlasAnimation& Anim = entity->getComponent<AtlasAnimation>();
	Anim.insertMotionData(Atalasname, L"off", index, index);
}
void UIButton::initialize()
{
	__super::initialize();

	//this->setClick(true);
	//this->setMovable(false);
	//this->setLive(true);
	//this->setRender(true);



	entity->addComponent<StateMachine>(
		make_pair(L"idle", &UIState::Idle::instance),
		make_pair(L"on", &UIState::On::instance),
		make_pair(L"left", &UIState::Left::instance),
		make_pair(L"off", &UIState::Off::instance),
		make_pair(L"right", &UIState::Right::instance));

	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.changeState(L"idle");

	stateMachine.insertTransitionCondition(L"on", UIState::Transition::IDLE, L"idle");
	stateMachine.insertTransitionCondition(L"left", UIState::Transition::IDLE, L"idle");
	stateMachine.insertTransitionCondition(L"right", UIState::Transition::IDLE, L"idle");
	stateMachine.insertTransitionCondition(L"off", UIState::Transition::IDLE, L"idle");

	stateMachine.insertTransitionCondition(L"idle", UIState::Transition::ON, L"on");
	stateMachine.insertTransitionCondition(L"left", UIState::Transition::ON, L"on");
	stateMachine.insertTransitionCondition(L"right", UIState::Transition::ON, L"on");
	stateMachine.insertTransitionCondition(L"off", UIState::Transition::ON, L"on");

	stateMachine.insertTransitionCondition(L"idle", UIState::Transition::OFF, L"off");
	stateMachine.insertTransitionCondition(L"on", UIState::Transition::OFF, L"off");

	stateMachine.insertTransitionCondition(L"on", UIState::Transition::LEFT, L"left");
	stateMachine.insertTransitionCondition(L"idle", UIState::Transition::LEFT, L"left");

	stateMachine.insertTransitionCondition(L"on", UIState::Transition::RIGHT, L"right");
	stateMachine.insertTransitionCondition(L"idle", UIState::Transition::RIGHT, L"right");
}

bool UIButton::OnMouse()
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	ASSERT_MESSAGE_RETURN(entity->hasComponent<Transform>(), "Controller need transform component",false);
	if (entity->getComponent<Ray>().rayCastCollider2D(entity->getComponent<BoxCollider>().getColliderRect2D()))
	{
		entity->getComponent<AtlasAnimation>().changeMotion(L"on");

		stateMachine.changeState(L"on");
		return true;
	}
	return false;

}
bool UIButton::OnClick()
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	ASSERT_MESSAGE_RETURN(entity->hasComponent<Transform>(), "Controller need transform component",false);


	if (OnMouse())
	{
		
		if ((Input.mousePressing(InputManager::MOUSEBUTTONTYPE::LEFT)))
		{
			entity->getComponent<AtlasAnimation>().changeMotion(L"left");
			stateMachine.changeState(L"left");
			return true;
		}
		if ((Input.mousePressing(InputManager::MOUSEBUTTONTYPE::RIGHT)))
		{
			stateMachine.changeState(L"right");
			return true;
		}
	}
	
	return false;

}
bool UIButton::OnIdle()
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	ASSERT_MESSAGE_RETURN(entity->hasComponent<Transform>(), "Controller need transform component",false);

	if (!entity->getComponent<Ray>().rayCastCollider2D(entity->getComponent<BoxCollider>().getColliderRect2D()))
	{
		entity->getComponent<AtlasAnimation>().changeMotion(L"idle");
		stateMachine.changeState(L"idle");
		return true;
	}
	else
		return false;
}


void UIButton::update()
{

	//Input.getMousePosition(x, y);
	//ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "Player Controller need transform component");
	//Transform& transform = entity->getComponent<Transform>();
	//AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	//StateMachine& stateMachine = entity->getComponent<StateMachine>();

	//Sound& sound = entity->getComponent<Sound>();
	//fighter_tigerstriker& tigerstriker = entity->getComponent<fighter_tigerstriker>();


	//충돌계산.
	OnIdle();
	OnMouse();
	OnClick();
}
void UIButton::lateUpdate()
{

}
void UIButton::render()
{
}
void UIButton::release()
{

}
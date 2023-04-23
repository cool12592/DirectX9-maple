#include "stdafx.h"
#include "OtherPlayerController.h"
#include "ExcelLoader.h"
OtherPlayerController::OtherPlayerController(wstring className, _vec3 position):className_(className), initPosition_(position),onMouse_(false)
{
}

void OtherPlayerController::initialize()
{
	entity->addComponent<Transform>(initPosition_,_vec3(0.f,0.f,0.f),_vec3(1.f,1.f,1.f));
	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
	entity->addComponent<BoxCollider>(_vec3(0.f, 100.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(100.f, 100.f, 10.f));

	
	entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(DEFAULT_USER_PIVOT_X, DEFAULT_USER_PIVOT_Y));

	entity->getComponent<Transform>().isInterpolate_ = true;
	//entity->getComponent<AtlasAnimation>().isInterpolate_ = true;

	ExcelLoader::loadOtherPlayerData(L"../ExcelFiles/PlayerInfo.xlsx", entity, className_.c_str());


}

void OtherPlayerController::update()
{
}

void OtherPlayerController::lateUpdate()
{
}

void OtherPlayerController::render()
{
	if (onMouse_)
		entity->getComponent<AtlasAnimation>().readyShaderValues(make_pair("onOutline", onMouse_), make_pair("outlineTimer", 0.f));
}

void OtherPlayerController::release()
{
}

#include "stdafx.h"
#include "OtherEnemyController.h"

OtherEnemyController::OtherEnemyController(int subType, _vec3 position, _vec2 pivot):initPosition_(position), subType_(subType),initPivot_(pivot)
{
}

OtherEnemyController::~OtherEnemyController()
{
}

void OtherEnemyController::initialize()
{
	entity->addComponent<Transform>(initPosition_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	if (0 == subType_)
		anim.insertSprite(L"monster", L"../AtlasFiles/Enemy/monster1.png", L"../AtlasFiles/Enemy/monster1.json");
	else if(1==subType_)
		anim.insertSprite(L"monster", L"../AtlasFiles/Enemy/Imposter.png", L"../AtlasFiles/Enemy/Imposter.json");
	else if(2==subType_)
		anim.insertSprite(L"monster", L"../AtlasFiles/Enemy/ADmonster.png", L"../AtlasFiles/Enemy/ADmonster.json");
	else if(3==subType_)
		anim.insertSprite(L"monster", L"../AtlasFiles/Enemy/mandarin.png", L"../AtlasFiles/Enemy/mandarin.json");
	anim.changeCurrentSprite(L"monster");
	anim.setUserPivot(initPivot_);

	entity->getComponent<Transform>().isInterpolate_ = true;
}

void OtherEnemyController::update()
{
}

void OtherEnemyController::lateUpdate()
{
}

void OtherEnemyController::render()
{
}

void OtherEnemyController::release()
{
}

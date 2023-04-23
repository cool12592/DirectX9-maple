#include "stdafx.h"
#include "TestController.h"

void TestController::initialize()
{
	entity->addComponent<Transform>(_vec3(100.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(0.5f, 0.5f, 1.f));
	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
	entity->addComponent<BoxCollider>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(200.f, 200.f, 1.f));

	/*entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	entity->getComponent<Sprite>().insertTexture(L"../AtlasFiles/Character/Blaze/blaze_idle.png");*/
	entity->getComponent<AtlasAnimation>().insertSprite(L"idle", L"../AtlasFiles/Character/Blaze/blaze_idle.png", L"../AtlasFiles/Character/Blaze/blaze_idle.json");
	entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"idle");
}

void TestController::update()
{
}

void TestController::lateUpdate()
{
}

void TestController::render()
{
}

void TestController::release()
{
}

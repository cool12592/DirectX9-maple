#include "stdafx.h"
#include "BackGroundFar.h"


void BackGroundFar::initialize()
{
	entity->addComponent<Transform>(_vec3(-500.f, 200.f, 10000.0f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));

	entity->addComponent<BoxCollider>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(200.f, 200.f, 1.f));

	entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	entity->getComponent<Sprite>().SetMultiple(5, 1);
	entity->getComponent<Sprite>().setAddPos(_vec3(0.f, 0.f, -10000.f));
	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/Map/2.png");
}

void BackGroundFar::update()
{
}

void BackGroundFar::lateUpdate()
{
}

void BackGroundFar::render()
{
}

void BackGroundFar::release()
{
}

#include "stdafx.h"
#include "BackGround.h"


void BackGround::initialize()
{
	entity->addComponent<Transform>(_vec3(-8.f, -260.f, -1.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));


	entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/Map/front2.png");


	entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/Map/front3.png");
	entity->getComponent<Sprite>().setAddPos(_vec3(210.f, -25.f, 0.f));

	entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/Map/front4.png");
	entity->getComponent<Sprite>().setAddPos(_vec3(255.f, 10.f, 0.f));

	entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/Map/front.png");
	entity->getComponent<Sprite>().setAddPos(_vec3(-416.f, 67.f, 0.f));

	entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/Map/front6.png");
	entity->getComponent<Sprite>().setAddPos(_vec3(-373.f, 51.f, 0.f));
}

void BackGround::update()
{
}

void BackGround::lateUpdate()
{
}

void BackGround::render()
{
}

void BackGround::release()
{
}

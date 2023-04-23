#include "stdafx.h"
#include "Tile.h"


void Tile::initialize()
{
	entity->addComponent<Transform>(_vec3(-3000.f, -360.f, 8000.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));

	entity->addComponent<BoxCollider>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(200.f, 200.f, 1.f));

	entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	entity->getComponent<Sprite>().SetMultiple(20, 4);
	entity->getComponent<Sprite>().setAddPos(_vec3(0.f, 0.f, -8000.f));

	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/Map/0.png");
}

void Tile::update()
{
}

void Tile::lateUpdate()
{
}

void Tile::render()
{
}

void Tile::release()
{
}

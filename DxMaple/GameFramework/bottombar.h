#pragma once
#include "MonoBehaviour.h"
class bottombar : public MonoBehaviour {
public:

void initialize()
	{

		//background
		_vec3 basicPos = _vec3(0, 0, 0.0f);

		entity->addComponent<Transform>(basicPos, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));

		//bottom
		_vec3 pos = _vec3(0, -190, -90.f);

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAddPos(pos);
		entity->getComponent<AtlasAnimation>().insertSprite(L"Bottom", L"../resource/kjs/ui/json/bottom_bar.png", L"../resource/kjs/ui/json/bottom_bar.json");
		entity->getComponent<AtlasAnimation>().isZRender = false;

	}
void update() {};
void lateUpdate() {};
void render() {};
void release() {};
};
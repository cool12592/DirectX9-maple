#pragma once
#include "MonoBehaviour.h"
class playerHP : public MonoBehaviour {
public:
	void initialize()
	{
		//background
		_vec3 basicPos = _vec3(0, 0, 0.0f);

		entity->addComponent<Transform>(basicPos, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));

		//HP

		_vec3 pos = _vec3(-280, -190, -90.f);

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAddPos(pos);
		entity->getComponent<AtlasAnimation>().insertSprite(L"HP", L"../resource/kjs/ui/json/HP.png", L"../resource/kjs/ui/json/HP.json");
		entity->getComponent<AtlasAnimation>().isZRender = false;
	}
	void update() {};
	void lateUpdate() {};
	void render() {};
	void release() {};
};
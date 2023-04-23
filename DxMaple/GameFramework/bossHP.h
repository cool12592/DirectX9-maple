#pragma once
#include "MonoBehaviour.h"
class bossHP : public MonoBehaviour {
public:
	void initialize()
	{
		//background
		_vec3 basicPos = _vec3(0, 0, 0.0f);

		entity->addComponent<Transform>(basicPos, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));

		_vec3 pos = _vec3(-280, -290, 0.f);

		entity->addComponent<Sprite>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<Sprite>().setAddPos(basicPos);
		entity->getComponent<Sprite>().insertTexture(L"../resource/kjs/ui/json/boss_hp.png");
		entity->getComponent<Sprite>().SetMultiple(4, 1);

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAddPos(basicPos);

		entity->getComponent<AtlasAnimation>().insertSprite(L"enemyHP", L"../resouce/kjs/ui/json/enemyHP.png", L"../resouce/kjs/ui/json/enemyHP.json");
		entity->getComponent<AtlasAnimation>().isZRender = false;

		//entity->setActive(false);
	}
	void update() {};
	void lateUpdate() {};
	void render() {};
	void release() {};
};
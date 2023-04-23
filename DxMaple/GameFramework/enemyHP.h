#pragma once
#include "MonoBehaviour.h"
class enemyHP : public MonoBehaviour {
public:

	void initialize()
	{
		_vec3 basicPos = _vec3(0, 0, 0.0f);

		entity->addComponent<Transform>(basicPos, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));

		//HP

		_vec3 posHP = _vec3(-40, 40, -90);
		//entity->addComponent<Sprite>(L"AtlasBuffer", L"AtlasShader");
		//entity->getComponent<Sprite>().setAddPos(posHP);
		//entity->getComponent<Sprite>().insertTexture(L"../resource/kjs/ui/json/enemy_hp.png");
		//entity->getComponent<Sprite>().SetMultiple(4, 1);

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAddPos(posHP);
		entity->getComponent<AtlasAnimation>().insertSprite(L"monsterHP", L"../resouce/kjs/ui/json/enemyHP.png", L"../resouce/kjs/ui/json/enemyHP.json");
		entity->getComponent<AtlasAnimation>().isZRender = false;

	}
	void update() {};
	void lateUpdate() {};
	void render() {};
	void release() {};
};

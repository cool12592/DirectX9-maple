#include "stdafx.h"
#include "Number.h"
#include "Item.h"

void Number::initialize()
{

	//¾ÆÀÌÅÛ°¹¼ö
	if (type_ == 0) {
		entity->addComponent<Transform>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(0.6f, 0.6f, 1.f));
		entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
		entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_0.png");
		//entity->getComponent<Sprite>().destBlendOp_ = D3DBLEND_DESTALPHA;
		//entity->getComponent<Sprite>().blendEnable_ = false;
	}
	if (type_ == 1) {

		entity->addComponent<Transform>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(0.6f, 0.6f, 1.f));
		entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
		entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_1.png");
		//entity->getComponent<Sprite>().destBlendOp_ = D3DBLEND_DESTALPHA;
		//entity->getComponent<Sprite>().blendEnable_ = false;
	}
	if (type_ == 2) {
		entity->addComponent<Transform>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(0.6f, 0.6f, 1.f));
		entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
		entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_2.png");
	}
	if (type_ == 3) {
		entity->addComponent<Transform>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(0.6f, 0.6f, 1.f));
		entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
		entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_3.png");
	}
	if (type_ == 4) {
		entity->addComponent<Transform>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(0.6f, 0.6f, 1.f));
		entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
		entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_4.png");
	}
	if (type_ == 5) {
		entity->addComponent<Transform>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(0.6f, 0.6f, 1.f));
		entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
		entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_5.png");
	}
	if (type_ == 6) {
		entity->addComponent<Transform>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(0.6f, 0.6f, 1.f));
		entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
		entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_6.png");
	}
	if (type_ == 7) {
		entity->addComponent<Transform>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(0.6f, 0.6f, 1.f));
		entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
		entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_7.png");
	}
	if (type_ == 8) {
		entity->addComponent<Transform>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(0.6f, 0.6f, 1.f));
		entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
		entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_8.png");
	}
	if (type_ == 9) {
		entity->addComponent<Transform>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(0.6f, 0.6f, 1.f));
		entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
		entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_9.png");

	}
}

void Number::update()
{
	if(itemEntity_->getComponent<Item>().pressed_==false)
	entity->getComponent<Transform>().position_ = itemEntity_->getComponent<Transform>().position_+_vec3(-14.f+add_*6.f,-10.f,-1.f);
}

void Number::lateUpdate()
{
}

void Number::render()
{
}

void Number::release()
{
}

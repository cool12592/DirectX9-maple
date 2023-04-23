#include "stdafx.h"
#include "Door.h"
#include "PlayerController.h"
#include "OtherPlayerController.h"
#include "GameManager.h"
void Door::initialize()
{
	entity->addComponent<Transform>(_vec3(0.f, 0.f,0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	entity->addComponent<BoxCollider>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(50.f, 50.f, 100.f));

	
	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
	entity->getComponent<AtlasAnimation>().setAnimationSpeed(6.f);
	//entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(0.f, 60.f));
	entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;
			

	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	anim.insertSprite(L"door", L"../AtlasFiles/Map/portal.png", L"../AtlasFiles/Map/portal.json");
	anim.changeCurrentSprite(L"door");





	entity->getComponent<BoxCollider>().bindColliderFunction(
		bind(&Door::enterCollider, this, placeholders::_1),
		bind(&Door::stayCollider, this, placeholders::_1),
		bind(&Door::exitCollider, this, placeholders::_1));
}

void Door::update()
{
	if (onTimer_)
	{
		if (timer_ <= activeTimer_)
		{
			timer_ += Time.getDeltaTime();
		}
	}

	onFade();


	if (onTimer_ && timer_ < activeTimer_)
		return;

	//if ((int)players_.size() == 1) // GameManager::getInstance()->getTotalPlayer())
	///*{
	//	isEnterDoor_ = true;
	//}
	//else
	//	isEnterDoor_ = false;*/

}

void Door::render()
{
	//if (fadeValue_ < 1.f&&fadeValue_>0.f)
	//{
	//	//Device.getRenderTargetPtr()->readyShaderValues(make_pair("isFade", true), make_pair("fadeValue", fadeValue_));
	//	Device.getRenderTargetPtr()->readyShaderValues(make_pair("isPixelate", true), make_pair("pixelateRatio", powf((1.f-fadeValue_)*10.f,2.f)));

	//}
	//else
	//{
	//	//Device.getRenderTargetPtr()->readyShaderValues(make_pair("isFade", false), make_pair("fadeValue", fadeValue_));
	//	Device.getRenderTargetPtr()->readyShaderValues(make_pair("isPixelate", false), make_pair("pixelateRatio", powf((1.f - fadeValue_) * 10.f, 2.f)));

	//}
//	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	//anim.destBlendOp_ = D3DBLEND_DESTALPHA;
	//anim.readyShaderValues(make_pair("onVanish", true), make_pair("vanishAlpha", 0.7f));

}

void Door::checkAndChangeScene()
{
	//if (NetworkManager::getInstance()->networkStruct_.party.hostIDN_!=-1&&NetworkManager::getInstance()->networkStruct_.party.hostIDN_ != NetworkManager::getInstance()->thisUser_.userIDN_)
	//	return;

	if (isEnterDoor_ && fadeValue_ >= 1.f)
	{
		players_.clear();
		GameManager::getInstance()->changeSceneAllPlayer(sceneName_);
	}
	
}

void Door::enterCollider(Entity * colliderEntity)
{

	if (colliderEntity->getType() == Entity::ENTITYTYPE::PLAYER)
	{

		if (colliderEntity->hasComponent<PlayerController>() || colliderEntity->hasComponent<OtherPlayerController>())
		{
			/*cout << "¹®µé¾î¿È" << endl;
			auto find_iter = find(players_.begin(), players_.end(), colliderEntity);
			if (players_.end() == find_iter)
				players_.emplace_back(colliderEntity);*/
			isEnterDoor_ = true;
		}
	}
}

void Door::stayCollider(Entity* colliderEntity)
{
	


	
}

void Door::exitCollider(Entity * colliderEntity)
{
	if (colliderEntity->getType() == Entity::ENTITYTYPE::PLAYER)
	{

		if (colliderEntity->hasComponent<PlayerController>() || colliderEntity->hasComponent<OtherPlayerController>())
		{

		/*	auto find_iter = find(players_.begin(), players_.end(), colliderEntity);
			if (players_.end() != find_iter)
				players_.erase(find_iter);*/
			isEnterDoor_ =false;
		}
	}
}

void Door::setOnActiveTimer(float timer)
{
	onTimer_ = true;
	activeTimer_ = timer;
	timer_ = 0.f;
}

void Door::onFade()
{
	if (!isEnterDoor_)
		fadeValue_ = clamp(fadeValue_ -= TimeManager::getInstance()->getDeltaTime(), 0.f, 1.f);
	else
		fadeValue_ = clamp(fadeValue_ += TimeManager::getInstance()->getDeltaTime(), 0.f, 1.f);

}

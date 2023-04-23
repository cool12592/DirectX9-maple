#include "stdafx.h"
#include "Nenguard.h"
#include "GameManager.h"
//#include "MandarinState.h"
//#include "Mandarin.h"
void Nenguard::initialize()
{
	entity->addComponent<Transform>(_vec3(0.f, 0.f, -2.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");

	entity->getComponent<AtlasAnimation>().setAnimationSpeed(16.f);
	entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(50-10, 65+20));
	//entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(90, 120));
	entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;


	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.insertSprite(L"nenguardstart", L"../AtlasFiles/Enemy/effect/nenguardstart.png", L"../AtlasFiles/Enemy/effect/nenguardstart.json");
	anim.insertSprite(L"nenguard", L"../AtlasFiles/Enemy/effect/nenguard.png", L"../AtlasFiles/Enemy/effect/nenguard.json");
	anim.changeCurrentSprite(L"nenguardstart");
	atlasPath_ = L"../AtlasFiles/Enemy/effect/nenguard";
	//entity->addComponent<BoxCollider>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(100.f, 100.f, 100.f));
	//entity->getComponent<BoxCollider>().bindColliderFunction(
	//	bind(&Nenguard::enterCollider, this, placeholders::_1),
	//	bind(&Nenguard::stayCollider, this, placeholders::_1),
	//	bind(&Nenguard::exitCollider, this, placeholders::_1));

	//hitbox_ = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	//hitbox_->setTypeAndName(Entity::ENTITYTYPE::UNKNOWN, L"enemyhitbox");
	//hitbox_->addComponent<GsSujueAKBOX>();
	//EntityManager::getInstance()->insertEntity(hitbox_);
	

}

void Nenguard::update()
{
	
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	if(anim.isSpriteEnd() && anim.getCurrentAnim()==L"nenguardstart")
		anim.changeCurrentSprite(L"nenguard");

	//setEffectData();

}

void Nenguard::lateUpdate()
{
}

void Nenguard::render()
{
}

void Nenguard::release()
{
}
void Nenguard::getDamage(float damage)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.changeState(L"hitted");
}

void Nenguard::setDirection()
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	_vec3 pos = entity->getComponent<Transform>().position_;
	auto p = GameManager::getInstance()->getPlayer();
	_vec3 p_pos = p->getComponent<Transform>().position_;

	if (p_pos.x > pos.x)
		anim.setRight(true);
	else
		anim.setRight(false);
}
//
//void Nenguard::setEffectData()
//{
//	if (L"" == atlasPath_)
//		return;
//	if (!entity->hasComponent<Transform>() || !entity->hasComponent<AtlasAnimation>())
//		return;
//
//	Transform& transform = entity->getComponent<Transform>();
//	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
//
//	unique_ptr<UdpEffect> effectData = make_unique<UdpEffect>();
//	int userIDN, entityNumber;
//	Entity::ENTITYTYPE entityType;
//	entity->getEntityNetworkInfo(userIDN, entityNumber, entityType);
//
//	effectData->objectType_ = 6;
//
//	effectData->userIDN_ = userIDN;
//	effectData->objectNumber_ = entityNumber;
//
//	effectData->effectName_ = string(atlasPath_.begin(), atlasPath_.end());
//	effectData->currentSpriteIndex_ = anim.getCurrentIndex();
//	effectData->pX_ = transform.position_.x;
//	effectData->pY_ = transform.position_.y;
//	effectData->pZ_ = transform.position_.z;
//	effectData->sizeX_ = transform.scale_.x;
//	effectData->sizeY_ = transform.scale_.y;
//	effectData->sizeZ_ = transform.scale_.z;
//
//	effectData->pivotX_ = anim.getUserPivot().x;
//	effectData->pivotY_ = anim.getUserPivot().y;
//	effectData->isRight_ = anim.getIsRight();
//
//
//	NetworkManager::getInstance()->thisUser_.udpDataList_.push_back(move(effectData));
//}

//void Nenguard::Attack()
//{
//	isAttacking = true;
//	StateMachine& stateMachine = entity->getComponent<StateMachine>();
//	stateMachine.transitionState(ATTACK);
//}

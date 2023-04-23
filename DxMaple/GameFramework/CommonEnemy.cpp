#include "stdafx.h"
#include "CommonEnemy.h"
#include "PlayerController.h"
#include "GameManager.h"
#include "CommonEnemyState.h"
#include "ExcelLoader.h"

void CommonEnemy::initialize()
{
	entity->addComponent<Transform>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
	entity->addComponent<BoxCollider>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(50.f, 70.f, 70.f));




	entity->getComponent<BoxCollider>().bindColliderFunction(
		bind(&CommonEnemy::enterCollider, this, placeholders::_1),
		bind(&CommonEnemy::stayCollider, this, placeholders::_1),
		bind(&CommonEnemy::exitCollider, this, placeholders::_1));


	entity->getComponent<AtlasAnimation>().setAnimationSpeed(8.f);

	entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(0.f, 0.f));
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	//¾ÆÀÌÅÛ
	entity->addComponent<ItemComponent>();


	//½ºÅÝ
	entity->addComponent<Status>();
	entity->getComponent<Status>().setDamagedFunction(bind(&CommonEnemy::getDamaged, this, placeholders::_1));

	entity->addComponent<Rigidbody>().setMass(1.f);
	entity->getComponent<Rigidbody>().setDrag(DRAG_LIMIT);
	//entity->getComponent<Rigidbody>().setUseGravity(false);

	if (name_ == L"ÃÊ·Ï¹ö¼¸")
		entity->getComponent<ItemComponent>().ownItem(make_pair(L"ÃÊ·Ï¹ö¼¸ÀÇ °«", 100), make_pair(L"coin", 100));

	else if (name_ ==L"½ºÅæ°ñ·½")
		entity->getComponent<ItemComponent>().ownItem(make_pair(L"½ºÅæ°ñ·½ÀÇ µ¹Á¶°¢", 100), make_pair(L"money", 100));
	
	else if (name_ == L"´ÙÅ©½ºÅæ°ñ·½")
		entity->getComponent<ItemComponent>().ownItem(make_pair(L"´ÙÅ© ½ºÅæ°ñ·½ÀÇ µ¹Á¶°¢", 100), make_pair(L"money", 100));


	else if (name_ == L"½ºÄÌ·¹Åæ")
		entity->getComponent<ItemComponent>().ownItem(make_pair(L"½ºÄÌ·¹°ïÀÇ »Ô", 100), make_pair(L"money", 100),make_pair(L"¸¶À» ±ÍÈ¯ ÁÖ¹®¼­",40));

	

	

	 if (name_ == L"ÁÖÈ²¹ö¼¸")
	{
		entity->getComponent<ItemComponent>().ownItem(make_pair(L"ÁÖÈ² ¹ö¼¸ÀÇ °«", 100), make_pair(L"money", 100),make_pair(L"»ç°ú",40));
		entity->getComponent<Rigidbody>().setUseGravity(true);

	}
	

	ExcelLoader::loadEnemyData(L"../ExcelFiles/EnemyInfo3.xlsx", entity, name_);




	///////////////////////////////////////////½ºÅ×ÀÌÆ®


	entity->addComponent<StateMachine>(
		make_pair(L"idle", &CommonEnemyState::Idle::instance),
		make_pair(L"move", &CommonEnemyState::Move::instance),
		make_pair(L"attack", &CommonEnemyState::Attack::instance),
		make_pair(L"damaged", &CommonEnemyState::BeHitted::instance),
		make_pair(L"die", &CommonEnemyState::Die::instance)
		);
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.changeState(L"move");



	stateMachine.insertTransitionCondition(L"move", IDLE, L"idle");
	stateMachine.insertTransitionCondition(L"idle", MOVE, L"move");
	stateMachine.insertTransitionCondition(L"damaged", HITTEDTOMOVE, L"attack");
	stateMachine.insertTransitionCondition(L"attack", MOVE, L"move");












	


}

void CommonEnemy::update()
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	Rigidbody &rb= entity->getComponent<Rigidbody>();



	
	if (entity->getComponent<Status>().hp_ <= 0)
	{

		isLife_ = false;

	}

	if (!isLife_)
	{

		if (stateMachine.getCurrentStateName() != L"die")
		{
			entity->getComponent<BoxCollider>().setBoxActive(false);
			entity->getComponent<ItemComponent>().dropItem();
			anim.setUserPivot(_vec2(0.f, -15.f));
			//entity->getComponent<Rigidbody>().setUseGravity(false);
			stateMachine.changeState(L"die");
		}
		if (anim.isSpriteEnd())
			entity->setActive(false);
	}







	
	
	
	

	//if ((stateMachine.getCurrentStateName() == L"idle" || stateMachine.getCurrentStateName() == L"move") && operation_ && isLife_)
	//	isAwake_ = true;
	//else
	//	isAwake_ = false;
	//if (stateMachine.getCurrentStateName() == L"attack" && stateMachine.getCurrentStateName() == L"attack2")
	//	isAttacking_ = true;
	//else
	//	isAttacking_ = false;


	if (name_ == L"ÁÖÈ²¹ö¼¸")
	{
		if (entity->getComponent<AtlasAnimation>().getCurrentMotionName() == L"move" || entity->getComponent<AtlasAnimation>().getCurrentMotionName() == L"attack")
		{
			static float jumpTimer = 0.f;
			jumpTimer += TimeManager::getInstance()->getDeltaTime();
			if (jumpTimer > 3.f)
			{
				jumpTimer = 0.f;
				int random = rand() % 2;
				if (random == 1)
				{
					entity->getComponent<Rigidbody>().setUseGravity(true);
					entity->getComponent<Rigidbody>().addForce(_vec3(0.f, 200.f, 0.f));
				}
			
			}
			
		}
		if(entity->getComponent<Rigidbody>().onGround_)
		{
			entity->getComponent<Rigidbody>().setUseGravity(false);
			entity->getComponent<Transform>().position_.y = -252.f;
		}
	}


}

void CommonEnemy::lateUpdate()
{
}

void CommonEnemy::render()
{

}
void CommonEnemy::release()
{
}




void CommonEnemy::getDamaged(Entity * attackboxEntity)
{

	if (!isLife_)return;
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	//if (stateMachine.getCurrentStateName() == L"damaged") return;

	float myX = entity->getComponent<Transform>().position_.x;
	float attackBoxX = attackboxEntity->getComponent<Transform>().position_.x;

	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();


	_vec3 direction;
	//¿À¸¥ÂÊ¿¡¼­ ¿Â °ø°ÝÀÌ¸é ¿ÞÂÊÀ¸·ÎÆ¨±è
	if (myX < attackBoxX)
		direction = { -0.7f, 0.f, 0.f };
	else
		direction = { +0.7f, 0.f, 0.f };

	rigidbody.setForce((rigidbody.direction_ + direction) * ATTACK_ACCEL);



	stateMachine.changeState(L"damaged");
}
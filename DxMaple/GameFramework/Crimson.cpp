#include "stdafx.h"
#include "Crimson.h"
#include "PlayerController.h"
#include "GameManager.h"
#include "CrimsonState.h"

void Crimson::initialize()
{
	entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
	entity->addComponent<BoxCollider>(_vec3(0.f, -30.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(180.f, 150.f, 50.f));




	entity->getComponent<BoxCollider>().bindColliderFunction(
		bind(&Crimson::enterCollider, this, placeholders::_1),
		bind(&Crimson::stayCollider, this, placeholders::_1),
		bind(&Crimson::exitCollider, this, placeholders::_1));


	entity->getComponent<AtlasAnimation>().setAnimationSpeed(8.f);

	//entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(196.f, 276.f));


	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.insertSprite(L"monster1", L"../AtlasFiles/Enemy/Crimson/CrimsonAtllas.png", L"../AtlasFiles/Enemy/Crimson/CrimsonAtllas.json");
	anim.changeCurrentSprite(L"monster1");

	anim.insertMotionData(L"monster1", L"idle", 0, 3);
	anim.insertMotionData(L"monster1", L"move", 4, 7);
	anim.insertMotionData(L"monster1", L"damaged", 8, 8);
	anim.insertMotionData(L"monster1", L"damaged0", 8, 8);
	anim.insertMotionData(L"monster1", L"attack", 9, 16);
	anim.insertMotionData(L"monster1", L"attack2", 17, 21);
	anim.insertMotionData(L"monster1", L"appear", 13, 13);
	anim.insertMotionData(L"monster1", L"die", 22, 40);
	anim.changeMotion(L"idle");

	entity->addComponent<Rigidbody>().setMass(1.f);
	entity->getComponent<Rigidbody>().setDrag(DRAG_LIMIT);


	entity->addComponent<Status>();
	entity->getComponent<Status>().setStatus(Status::CLASSTYPE::ETC, 20000, 0, 1000, 0, 0, 0, 0, 0, 0);
	entity->getComponent<Status>().setDamagedFunction(bind(&Crimson::getDamaged, this, placeholders::_1));
	entity->getComponent<Status>().setDownedFunction(bind(&Crimson::getDowned, this, placeholders::_1));



	///////////////////////////////////////////스테이트


	entity->addComponent<StateMachine>(
		make_pair(L"idle", &CrimsonState::Idle::instance),
		make_pair(L"move", &CrimsonState::Move::instance),
		make_pair(L"attack", &CrimsonState::Attack::instance),
		make_pair(L"attack2", &CrimsonState::Attack2::instance),
		make_pair(L"damaged", &CrimsonState::BeHitted::instance),
		make_pair(L"damaged0", &CrimsonState::BeHitted0::instance),
		make_pair(L"die", &CrimsonState::Die::instance)
		);
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.changeState(L"move");



	stateMachine.insertTransitionCondition(L"move", IDLE, L"idle");
	stateMachine.insertTransitionCondition(L"attack2", IDLE, L"idle");
	stateMachine.insertTransitionCondition(L"attack", IDLE, L"idle");



	stateMachine.insertTransitionCondition(L"move", ATTACK, L"attack");
	stateMachine.insertTransitionCondition(L"idle", ATTACK, L"attack");
//	stateMachine.insertTransitionCondition(L"attack", ATTACK, L"attack2");

	stateMachine.insertTransitionCondition(L"move", SKILL, L"attack2");
	stateMachine.insertTransitionCondition(L"idle", SKILL, L"attack2");


	stateMachine.insertTransitionCondition(L"idle", MOVE, L"move");
	stateMachine.insertTransitionCondition(L"attack", MOVE, L"move");
	stateMachine.insertTransitionCondition(L"attack2", MOVE, L"move");


	stateMachine.insertTransitionCondition(L"damaged", HITTEDTOMOVE, L"move");
	stateMachine.insertTransitionCondition(L"damaged0", HITTEDTOMOVE, L"move");


	 
	//공격체 세팅
	shared_ptr<Entity>& attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	attackBox->addComponent<AttackBox>();
	attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"attackbox");
	EntityManager::getInstance()->insertEntity(attackBox);

	attackBox_ = attackBox;


}

void Crimson::update()
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	_vec3 pos = entity->getComponent<Transform>().position_;
	auto p = GameManager::getInstance()->getPlayer();

	_vec3 p_pos = p->getComponent<Transform>().position_;
	D3DXVECTOR3 distance = entity->getComponent<Transform>().position_ - p_pos;
	float distanceY =fabs(entity->getComponent<Transform>().position_.y - p_pos.y);
	float fDis = D3DXVec3Length(&distance);

	attackCoolTime_ += TimeManager::getInstance()->getDeltaTime();


	
	



	if (entity->getComponent<Status>().hp_ <= 0)
	{
		//entity->getComponent<Status>().invincible_ = true;

		isLife_ = false;

	}

	if (!isLife_)
	{

		if (stateMachine.getCurrentStateName() != L"die")
		{
			//attackBox_.lock()->getComponent<AttackBox>().deactivate();
			anim.setUserPivot(_vec2(0.f, -15.f));
			entity->getComponent<Rigidbody>().setUseGravity(false);
			entity->getComponent<BoxCollider>().setBoxActive(false);
			stateMachine.changeState(L"die");
		}
		if (anim.isSpriteEnd())
			entity->setActive(false);
	}




	skillCoolTime_ += TimeManager::getInstance()->getDeltaTime();

	//가까이있을 때 쿨돌면 공격 아니면 대기 멀면 추적


	
	if (isAwake_)
	{
		if (distanceY < 30.f)
		{

			if (skillCoolTime_ > 6.f)
			{
				stateMachine.transitionState(SKILL);
				skillCoolTime_ = 0.f;
				attackCoolTime_ = 0.f;
			}

			else if (attackCoolTime_ > 4.f)
			{
				stateMachine.transitionState(ATTACK);
				attackCoolTime_ = 0.f;
			}
			else
			{
				stateMachine.transitionState(IDLE);
			}

		}
		else
		{

			stateMachine.transitionState(MOVE);
		}
	}
	


	if ((stateMachine.getCurrentStateName() == L"idle" || stateMachine.getCurrentStateName() == L"move")  && !isAttacking_)
		isAwake_ = true;
	else
		isAwake_ = false;

	if (stateMachine.getCurrentStateName() == L"attack" && stateMachine.getCurrentStateName() == L"attack2")
		isAttacking_ = true;
	else
		isAttacking_ = false;



	sendMonsterData();
}

void Crimson::lateUpdate()
{
}

void Crimson::render()
{
}

void Crimson::release()
{
}

void Crimson::Appear()
{

	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	_vec3	direction = { +3.f, 0.f, 0.f };

	rigidbody.setForce((rigidbody.direction_ + direction) * ATTACK_ACCEL);
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.changeMotion(L"appear");

}


void Crimson::getDamaged(Entity* attackboxEntity)
{
	if ((attackboxEntity->getName() == L"MagmaAttackbox" || attackboxEntity->getName() == L"NiddleAttackbox") && !trapHitted_)
		return;
	if (!isLife_)return;
	float myX = entity->getComponent<Transform>().position_.x;
	float attackBoxX = attackboxEntity->getComponent<Transform>().position_.x;

	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();


	_vec3 direction;
	//오른쪽에서 온 공격이면 왼쪽으로튕김
	if (myX < attackBoxX)
		rigidbody.direction_ = { -2.f, 0.f, 0.f };
	else
		rigidbody.direction_ = { +2.f, 0.f, 0.f };
	rigidbody.velocity_.y = 0.f;
	//rigidbody.setForce((rigidbody.direction_ + direction) * ATTACK_ACCEL);
	rigidbody.setForce(rigidbody.direction_ * 100.f);

	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.changeState(L"damaged0");
}
void Crimson::getDowned(Entity* attackboxEntity)
{
	
	if (!isLife_)return;
	float myX = entity->getComponent<Transform>().position_.x;
	float attackBoxX = attackboxEntity->getComponent<Transform>().position_.x;

	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();


	_vec3 direction;
	//오른쪽에서 온 공격이면 왼쪽으로튕김
	if (myX < attackBoxX)
		direction = { -3.f, 0.f, 0.f };
	else
		direction = { +3.f, 0.f, 0.f };

	rigidbody.setForce((rigidbody.direction_ + direction) * ATTACK_ACCEL);


	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.changeState(L"damaged");
}

void Crimson::sendMonsterData()
{/*
#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "Entity must need Transform component");
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<AtlasAnimation>(), "Entity must need AtlasAnimation component");
#endif
	Transform& transform = entity->getComponent<Transform>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	unique_ptr<UdpEnemy> enemyData = make_unique<UdpEnemy>();
	int userIDN, entityNumber;
	Entity::ENTITYTYPE entityType;
	entity->getEntityNetworkInfo(userIDN, entityNumber, entityType);

	enemyData->objectType_ = 2;

	enemyData->userIDN_ = userIDN;
	enemyData->objectNumber_ = entityNumber;
	enemyData->subType_ = 1;
	enemyData->currentSpriteIndex_ = anim.getCurrentIndex();
	enemyData->pX_ = transform.position_.x;
	enemyData->pY_ = transform.position_.y;
	enemyData->pZ_ = transform.position_.z;
	enemyData->pivotX_ = anim.getUserPivot().x;
	enemyData->pivotY_ = anim.getUserPivot().y;
	enemyData->isRight_ = anim.getIsRight();


	NetworkManager::getInstance()->thisUser_.udpDataList_.push_back(move(enemyData));*/
}

#include "stdafx.h"
#include "HornTailLeftState.h"
#include "PlayerController.h"
#include "GameManager.h"
//#include "HornTailState.h"

#include <ctime>
void HornTailLeft::initialize()
{




	
		entity->addComponent<Transform>(_vec3(-142.f , -90.f + 144.f / 2.f + 209.f / 2.f - 30.f, 101.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
		entity->addComponent<BoxCollider>(_vec3(-50.f, -80.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(50.f, 100.f, 50.f));

	

		entity->getComponent<BoxCollider>().bindColliderFunction(
			bind(&HornTailLeft::enterCollider, this, placeholders::_1),
			bind(&HornTailLeft::stayCollider, this, placeholders::_1),
			bind(&HornTailLeft::exitCollider, this, placeholders::_1));

 
		entity->addComponent<Rigidbody>().setMass(1.f);
		entity->getComponent<Rigidbody>().setDrag(DRAG_LIMIT);
		entity->getComponent<Rigidbody>().setUseGravity(false);

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAnimationSpeed(6.f);
		AtlasAnimation& anim1 = entity->getComponent<AtlasAnimation>();
		entity->getComponent<AtlasAnimation>().insertSprite(L"idle", L"../AtlasFiles/HornTail/lefthead.png", L"../AtlasFiles/HornTail/lefthead.json");
		
		entity->getComponent<AtlasAnimation>().insertSprite(L"breath1", L"../AtlasFiles/HornTail/Left/leftbreath-0.png", L"../AtlasFiles/HornTail/Left/leftbreath-0.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"breath2", L"../AtlasFiles/HornTail/Left/leftbreath-1.png", L"../AtlasFiles/HornTail/Left/leftbreath-1.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"skill", L"../AtlasFiles/HornTail/Skill/leftattack2.png", L"../AtlasFiles/HornTail/Skill/leftattack2.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"die", L"../AtlasFiles/HornTail/Die/leftdie.png", L"../AtlasFiles/HornTail/Die/leftdie.json");

		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"idle");
		anim1.setUserPivot(_vec2(0.f,0.f));




	entity->addComponent<Status>();
	entity->getComponent<Status>().setStatus(Status::CLASSTYPE::ETC, 100000, 0, 100, 0, 0, 0, 0, 0, 0);
	entity->getComponent<Status>().setDamagedFunction(bind(&HornTailLeft::getDamaged, this, placeholders::_1));
	entity->getComponent<Status>().setDownedFunction(bind(&HornTailLeft::getDowned, this, placeholders::_1));



	//공격체 세팅
	shared_ptr<Entity>& attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	attackBox->addComponent<AttackBox>();
	attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"attackbox");
	EntityManager::getInstance()->insertEntity(attackBox);

	attackBox_ = attackBox;



	////////////////////////////////
	//상태패턴
	entity->addComponent<StateMachine>(
		make_pair(L"idle", &HornTailLeftState::Idle::instance),
		make_pair(L"attack1", &HornTailLeftState::Attack1::instance),
		make_pair(L"attack2", &HornTailLeftState::Attack2::instance),
		make_pair(L"die", &HornTailLeftState::Die::instance)
		);
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.changeState(L"idle");

	stateMachine.insertTransitionCondition(L"attack1", IDLE, L"idle");
	stateMachine.insertTransitionCondition(L"attack2", IDLE, L"idle");
	stateMachine.insertTransitionCondition(L"idle", ATTACK, L"attack1");
	stateMachine.insertTransitionCondition(L"idle", SKILL, L"attack2");


	icePosition_ = GameManager::getInstance()->getIcePosition();










}
void HornTailLeft::update()
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();



	if (stateMachine.getCurrentStateName() == L"idle")
		fAttackTerm += TimeManager::getInstance()->getDeltaTime();


	if (fAttackTerm > 2.2f)
	{
		fAttackTerm = 0.f;
		int random = rand() % 100;
		if (random < 40)
		{
			stateMachine.transitionState(ATTACK);
		}
		if (random > 60)
		{
			stateMachine.transitionState(SKILL);
		}

	}

	if (entity->getComponent<Status>().hp_ <= 0)
	{
		if (stateMachine.getCurrentStateName() != L"die")
		{
			anim.setUserPivot(_vec2(0.f, -15.f));
			entity->getComponent<BoxCollider>().setBoxActive(false);
			stateMachine.changeState(L"die");
		}
	}
	


}

void HornTailLeft::lateUpdate()
{


}


void HornTailLeft::skillReset()
{
	pair<float, int> minSkill = make_pair(1000.f, -1);
	for (int i = 1; i < skillcooltime.size(); i++)
	{
		if (skillcooltime[i].first > 0)
		{
			if (minSkill.first > skillcooltime[i].first)
			{
				minSkill.first = skillcooltime[i].first;
				minSkill.second = i;
			}

		}
	}
	skillcooltime[minSkill.second].first = 0;
	readyskill.emplace_back(minSkill.second);

}
void HornTailLeft::render()
{


}


void HornTailLeft::release()
{
}
void HornTailLeft::getDamage(float damage)
{

	//StateMachine& stateMachine = entity->getComponent<StateMachine>();
	//stateMachine.changeState(L"hitted");
}

void HornTailLeft::setDirection()
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

void HornTailLeft::getDamaged(Entity* attackboxEntity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	if (anim.getCurrentMotionName() == L"skill4")
	{

		nenHP -= 100.f;
		if (nenHP <= 0)
			stateMachine.transitionState(NENGROGGY);
		Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
		_vec3 direction;
		direction = { +5.f, 0.f, 0.f };
		rigidbody.setForce((rigidbody.direction_ + direction) * ATTACK_ACCEL);


	}
}

void HornTailLeft::getDowned(Entity* attackboxEntity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	if (anim.getCurrentMotionName() == L"skill4")
	{

		nenHP -= 100.f;
		if (nenHP <= 0)
			stateMachine.transitionState(NENGROGGY);
		Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
		_vec3 direction;
		direction = { +5.f, 0.f, 0.f };
		rigidbody.setForce((rigidbody.direction_ + direction) * ATTACK_ACCEL);


	}
}

void HornTailLeft::Attack()
{

	StateMachine& stateMachine = entity->getComponent<StateMachine>();

	if (readyskill.size() == 0)//준비된 스킬이 없다면
	{
		isAttacking = true;
		stateMachine.transitionState(ATTACK);
		skillReset();

	}

	else
	{
		ind = rand() % readyskill.size();
		skillNumber = readyskill[ind];
		skillcooltime[skillNumber].first = skillcooltime[skillNumber].second;//쿨타임 초기화
		readyskill.erase(readyskill.begin() + ind); //레디스킬에서제거
		if (skillNumber == 0)
		{

			stateMachine.changeState(L"skill1"); //필살기
		}
		if (skillNumber == 1)
		{

			stateMachine.changeState(L"skill2"); //넨수
		}
		else if (skillNumber == 2)
		{

			stateMachine.changeState(L"skill3"); //넨꽃
		}
		else if (skillNumber == 3)
		{
			nenHP = 800.f;
			stateMachine.changeState(L"skill4"); //넨가드
		}

	}

}



//void HornTailLeft::sendMonsterData()
//{
//#ifdef _DEBUG
//	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "Entity must need Transform component");
//	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<AtlasAnimation>(), "Entity must need AtlasAnimation component");
//#endif
//	Transform& transform = entity->getComponent<Transform>();
//	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
//
//	unique_ptr<UdpEnemy> enemyData = make_unique<UdpEnemy>();
//	int userIDN, entityNumber;
//	Entity::ENTITYTYPE entityType;
//	entity->getEntityNetworkInfo(userIDN, entityNumber, entityType);
//
//	enemyData->objectType_ = 2;
//
//	enemyData->userIDN_ = userIDN;
//	enemyData->objectNumber_ = entityNumber;
//	enemyData->subType_ = 3;
//	enemyData->currentSpriteIndex_ = anim.getCurrentIndex();
//	enemyData->pX_ = transform.position_.x;
//	enemyData->pY_ = transform.position_.y;
//	enemyData->pZ_ = transform.position_.z;
//	enemyData->pivotX_ = anim.getUserPivot().x;
//	enemyData->pivotY_ = anim.getUserPivot().y;
//	enemyData->isRight_ = anim.getIsRight();
//
//
//	NetworkManager::getInstance()->thisUser_.udpDataList_.push_back(move(enemyData));
//}









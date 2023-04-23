#include "stdafx.h"
#include "HornTail.h"
#include "PlayerController.h"
#include "GameManager.h"
#include "HornTailState.h"

#include <ctime>
void HornTail::initialize()
{
	
	
	if (type_ == L"start")
	{
		entity->addComponent<Transform>(_vec3(10.f, 55.f, 100.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAnimationSpeed(7.f);
		entity->getComponent<AtlasAnimation>().insertSprite(L"start0", L"../AtlasFiles/HornTail/start-0.png", L"../AtlasFiles/HornTail/start-0.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"start1", L"../AtlasFiles/HornTail/start-1.png", L"../AtlasFiles/HornTail/start-1.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"start2", L"../AtlasFiles/HornTail/start-2.png", L"../AtlasFiles/HornTail/start-2.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"start3", L"../AtlasFiles/HornTail/start-3.png", L"../AtlasFiles/HornTail/start-3.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"start4", L"../AtlasFiles/HornTail/start-4.png", L"../AtlasFiles/HornTail/start-4.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"start5", L"../AtlasFiles/HornTail/start-5.png", L"../AtlasFiles/HornTail/start-5.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"start6", L"../AtlasFiles/HornTail/start-6.png", L"../AtlasFiles/HornTail/start-6.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"start7", L"../AtlasFiles/HornTail/start-7.png", L"../AtlasFiles/HornTail/start-7.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"start8", L"../AtlasFiles/HornTail/start-8.png", L"../AtlasFiles/HornTail/start-8.json");
		

	


		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"start0");
		//entity->getComponent<AtlasAnimation>().setAddPos(_vec3(215.f / 2.f, 0.f, 0.f));
	}

	if (type_ == L"body")
	{
	
		entity->addComponent<Transform>(_vec3(-130.f, -90.f, 5000.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));




		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
		entity->getComponent<Sprite>().insertTexture(L"../AtlasFiles/HornTail/tail.png");
		entity->getComponent<Sprite>().setAddPos(_vec3(215.f / 2.f + 170.f, -144.f / 2.f - 192.f / 2.f, 0.f));



		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAnimationSpeed(6.f);
		AtlasAnimation& anim9 = entity->getComponent<AtlasAnimation>();
		entity->getComponent<AtlasAnimation>().insertSprite(L"wing", L"../AtlasFiles/HornTail/wing.png", L"../AtlasFiles/HornTail/wing.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"wing");
		entity->getComponent<AtlasAnimation>().setAddPos(_vec3(215.f / 2.f, 0.f, 5000.f));

		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
		entity->getComponent<Sprite>().insertTexture(L"../AtlasFiles/HornTail/leg.png");
		entity->getComponent<Sprite>().setAddPos(_vec3(215.f / 2.f, -144.f / 2.f - 192.f / 2.f + 5.f, 0.f));



		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAnimationSpeed(6.f);
		AtlasAnimation& anim8 = entity->getComponent<AtlasAnimation>();
		entity->getComponent<AtlasAnimation>().insertSprite(L"leftHand", L"../AtlasFiles/HornTail/hand.png", L"../AtlasFiles/HornTail/hand.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"leftHand");

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAnimationSpeed(6.f);
		AtlasAnimation& anim7 = entity->getComponent<AtlasAnimation>();
		entity->getComponent<AtlasAnimation>().insertSprite(L"RightHand", L"../AtlasFiles/HornTail/hand.png", L"../AtlasFiles/HornTail/hand.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"magic", L"../AtlasFiles/HornTail/Skill/magic.png", L"../AtlasFiles/HornTail/Skill/magic.json");

		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"RightHand");
		entity->getComponent<AtlasAnimation>().setRight(false);
		entity->getComponent<AtlasAnimation>().setAddPos(_vec3(215.f - 1.f, 0.f, 0.f));
		


	}
	if (type_ == L"mid")
	{
		entity->addComponent<Transform>(_vec3(-130.f, -90.f, 100.99f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
		entity->addComponent<BoxCollider>(_vec3(100.f, -250.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(300.f, 200.f, 50.f));

		

		entity->getComponent<BoxCollider>().bindColliderFunction(
			bind(&HornTail::enterCollider, this, placeholders::_1),
			bind(&HornTail::stayCollider, this, placeholders::_1),
			bind(&HornTail::exitCollider, this, placeholders::_1));

		entity->getComponent<BoxCollider>().setBoxActive(false);

		entity->addComponent<Rigidbody>().setMass(1.f);
		entity->getComponent<Rigidbody>().setDrag(DRAG_LIMIT);
		entity->getComponent<Rigidbody>().setUseGravity(false);



		//오른쪽왼쪽 몸소환

		auto horntail1 = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		horntail1->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"HornTail");
		horntail1->addComponent<HornTailLeft>();
		EntityManager::getInstance()->insertEntity(horntail1);

		LeftHead = horntail1;

		auto horntail2 = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		horntail2->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"HornTail");
		horntail2->addComponent<HornTailRight>();
		EntityManager::getInstance()->insertEntity(horntail2);

		RightHead = horntail2;



		auto horntail3 = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		horntail3->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"HornTail");
		horntail3->addComponent<HornTail>(L"body");
		EntityManager::getInstance()->insertEntity(horntail3);

		body_ = horntail3;

		
		///////////////////


		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAnimationSpeed(6.f);
		AtlasAnimation& anim2 = entity->getComponent<AtlasAnimation>();
		entity->getComponent<AtlasAnimation>().insertSprite(L"idle", L"../AtlasFiles/HornTail/midhead.png", L"../AtlasFiles/HornTail/midhead.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"idle");

		entity->getComponent<AtlasAnimation>().insertSprite(L"breath1", L"../AtlasFiles/HornTail/midbreath-0.png", L"../AtlasFiles/HornTail/midbreath-0.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"breath2", L"../AtlasFiles/HornTail/midbreath-1.png", L"../AtlasFiles/HornTail/midbreath-1.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"skill", L"../AtlasFiles/HornTail/Skill/midattack2.png", L"../AtlasFiles/HornTail/Skill/midattack2.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"die", L"../AtlasFiles/HornTail/Die/middie.png", L"../AtlasFiles/HornTail/Die/middie.json");

		entity->getComponent<AtlasAnimation>().insertSprite(L"die0", L"../AtlasFiles/HornTail/Die/die-0.png", L"../AtlasFiles/HornTail/Die/die-0.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"die1", L"../AtlasFiles/HornTail/Die/die-1.png", L"../AtlasFiles/HornTail/Die/die-1.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"die2", L"../AtlasFiles/HornTail/Die/die-2.png", L"../AtlasFiles/HornTail/Die/die-2.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"die3", L"../AtlasFiles/HornTail/Die/die-3.png", L"../AtlasFiles/HornTail/Die/die-3.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"die4", L"../AtlasFiles/HornTail/Die/die-4.png", L"../AtlasFiles/HornTail/Die/die-4.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"die5", L"../AtlasFiles/HornTail/Die/die-5.png", L"../AtlasFiles/HornTail/Die/die-5.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"die6", L"../AtlasFiles/HornTail/Die/die-6.png", L"../AtlasFiles/HornTail/Die/die-6.json");

		//entity->getComponent<AtlasAnimation>().insertSprite(L"magic", L"../AtlasFiles/HornTail/Skill/magic.png", L"../AtlasFiles/HornTail/Skill/magic.json");



		entity->getComponent<AtlasAnimation>().setAddPos(_vec3(215.f / 2.f, 144.f / 2.f + 332.f / 2.f - 30.f, 0.f));

		entity->addComponent<Status>();
		entity->getComponent<Status>().setStatus(Status::CLASSTYPE::ETC, 100000, 0, 100, 0, 0, 0, 0, 0, 0);
		entity->getComponent<Status>().setDamagedFunction(bind(&HornTail::getDamaged, this, placeholders::_1));
		entity->getComponent<Status>().setDownedFunction(bind(&HornTail::getDowned, this, placeholders::_1));





		//공격체 세팅
		shared_ptr<Entity>& attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		attackBox->addComponent<AttackBox>();
		attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"attackbox");
		EntityManager::getInstance()->insertEntity(attackBox);

		attackBox_ = attackBox;



		////////////////////////////////
		//상태패턴
		entity->addComponent<StateMachine>(
			make_pair(L"idle", &HornTailState::Idle::instance),
			make_pair(L"attack1", &HornTailState::Attack1::instance),
			make_pair(L"attack2", &HornTailState::Attack2::instance),
			make_pair(L"die", &HornTailState::Die::instance),
			make_pair(L"horntaildie", &HornTailState::HornTailDie::instance)
			);
		StateMachine& stateMachine = entity->getComponent<StateMachine>();
		stateMachine.changeState(L"idle");

		stateMachine.insertTransitionCondition(L"attack1", IDLE, L"idle");
		stateMachine.insertTransitionCondition(L"attack2", IDLE, L"idle");
		stateMachine.insertTransitionCondition(L"idle", ATTACK, L"attack1");
		stateMachine.insertTransitionCondition(L"idle", SKILL, L"attack2");


		firePosition_ = GameManager::getInstance()->getFirePosition();
		icePosition_ = GameManager::getInstance()->getIcePosition();
		HornTail_totalHP = entity->getComponent<Status>().hp_ + LeftHead.lock()->getComponent<Status>().hp_ + RightHead.lock()->getComponent<Status>().hp_;

		hp_UI = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		hp_UI->addComponent<DNFUI>(DNFUI::UItype::bossRed, _vec3(-240.f, 300.f, -100.f));
		hp_UI->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"DNFUI");
		EntityManager::getInstance()->insertEntity(hp_UI);
		hp_UI->getComponent<DNFUI>().bossMaxHp = HornTail_totalHP;

		backHPui = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		backHPui->addComponent<DNFUI>(DNFUI::UItype::bossBack, _vec3(-240.f, 300.f, -100.f));
		backHPui->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"DNFUI");
		EntityManager::getInstance()->insertEntity(backHPui);

		icon_ui = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		icon_ui->addComponent<DNFUI>(DNFUI::UItype::bossIcon, _vec3(-240.f, 300.f, -100.f));
		icon_ui->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"DNFUI");
		EntityManager::getInstance()->insertEntity(icon_ui);
	}





	

}
void HornTail::update()
{


	if (type_ == L"start")
	{
		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		
		if (anim.isSpriteEnd())
		{
			if (anim.getCurrentAnim() == L"start8")
			{
				if (horntail != nullptr)
					return;
				horntail = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
				horntail->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"HornTail");
				horntail->addComponent<HornTail>(L"mid");
				EntityManager::getInstance()->insertEntity(horntail);
				GameManager::getInstance()->setBoss(horntail);
				entity->setActive(false);
			}
			else if (anim.getCurrentAnim() == L"start7")
				anim.changeCurrentSprite(L"start8");
			else if (anim.getCurrentAnim() == L"start6")
				anim.changeCurrentSprite(L"start7");
			else if (anim.getCurrentAnim() == L"start5")
				anim.changeCurrentSprite(L"start6");
			else if (anim.getCurrentAnim() == L"start4")
				anim.changeCurrentSprite(L"start5");
			else if (anim.getCurrentAnim() == L"start3")
				anim.changeCurrentSprite(L"start4");
			else if (anim.getCurrentAnim() == L"start2")
				anim.changeCurrentSprite(L"start3");
			else if (anim.getCurrentAnim() == L"start1")
				anim.changeCurrentSprite(L"start2");
			else if (anim.getCurrentAnim() == L"start0")
				anim.changeCurrentSprite(L"start1");

			

		}
	}

	if (type_ == L"body")
	{
		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		if (anim.getCurrentAnim() == L"magic"&&anim.isSpriteEnd())
		{
			anim.changeCurrentSprite(L"RightHand");
			anim.setAddPos(_vec3(214.f, 0.f, 0.f));
			anim.setRight(false);
		}
	}

	if (type_ == L"mid")
	{
		
		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		StateMachine& stateMachine = entity->getComponent<StateMachine>();
		
		
		if (entity->getComponent<Status>().hp_ <= 0.f)
		{
			if (stateMachine.getCurrentStateName() != L"horntaildie")
			{
				hp_UI->setActive(false);
				backHPui->setActive(false);
				icon_ui->setActive(false);
				stateMachine.changeState(L"horntaildie");
				entity->getComponent<BoxCollider>().setBoxActive(false);
			}
			return;
		}

		if (stateMachine.getCurrentStateName() == L"idle")
		{
			bodyAttackTerm += TimeManager::getInstance()->getDeltaTime();
			fAttackTerm += TimeManager::getInstance()->getDeltaTime();
		}
		
		

		if (fAttackTerm > 3.0f)
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
		//if (page_ == 2)
		{
			if (bodyAttackTerm > 2.5f)
			{
				bodyAttackTerm = 0.f;
				int random = rand() % 100;
				if (random < 30)
				{
					body_.lock()->getComponent<AtlasAnimation>().changeCurrentSprite(L"magic");
					body_.lock()->getComponent<AtlasAnimation>().setAddPos(_vec3(293.f, -30.f, 0.f));
					body_.lock()->getComponent<AtlasAnimation>().setRight(true);
				}
			}
		}
		
	
		if (page_==1)
		{
			if (RightHead.lock()->getComponent<Status>().hp_ + LeftHead.lock()->getComponent<Status>().hp_ <= 0)
			{
				page_ = 2;
				entity->getComponent<BoxCollider>().setBoxActive(true);
			}
		}

		
		if (entity->getComponent<Status>().hp_ <= entity->getComponent<Status>().maxHp_*0.5f)
		{
			if (stateMachine.getCurrentStateName() != L"die")
			{
				anim.setUserPivot(_vec2(0.f, -15.f));
				stateMachine.changeState(L"die");

			}
		}
		
		
		HornTail_totalHP = entity->getComponent<Status>().hp_ + LeftHead.lock()->getComponent<Status>().hp_ + RightHead.lock()->getComponent<Status>().hp_;

		
	}
	
		


	









}

void HornTail::lateUpdate()
{
	

}


void HornTail::skillReset()
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
void HornTail::render()
{


}


void HornTail::release()
{
}
void HornTail::getDamage(float damage)
{

	//StateMachine& stateMachine = entity->getComponent<StateMachine>();
	//stateMachine.changeState(L"hitted");
}

void HornTail::setDirection()
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

void HornTail::getDamaged(Entity* attackboxEntity)
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

void HornTail::getDowned(Entity* attackboxEntity)
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

void HornTail::Attack()
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


//
//void HornTail::sendMonsterData()
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
//








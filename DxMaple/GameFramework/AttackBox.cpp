#include "stdafx.h"
#include "AttackBox.h"
#include "EntityManager.h"
#include "GameManager.h"
void AttackBox::activateAttackBox(_vec3 position, _vec3 scale, USER user, float physicalDamage, float magicalDamage)
{
	Transform& transform = entity->getComponent<Transform>();
	BoxCollider& collider = entity->getComponent<BoxCollider>();

	transform.position_ = position;
	collider.transform_.scale_ = scale;
	user_ = user;
	physicalDamage_ = physicalDamage;
	magicalDamage_ = magicalDamage;
}

void AttackBox::activateAttackBox(const wchar_t * dataName, Entity * userEntity, const wchar_t* skillName)
{
#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(userEntity->hasComponent<AtlasAnimation>(), "user entity must have AtlasAnimation Component");
	ASSERT_MESSAGE_NULLRETURN(userEntity->hasComponent<Status>(), "user entity must have Status Component");
	ASSERT_MESSAGE_NULLRETURN(userEntity->hasComponent<Transform>(), "user entity must have Transform Component");


	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "entity must have Transform Component");
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<BoxCollider>(), "entity must have BoxCollider Component");

#endif
	AtlasAnimation& userAnim = userEntity->getComponent<AtlasAnimation>();
	Status& userStatus = userEntity->getComponent<Status>();
	Transform& userTransform = userEntity->getComponent<Transform>();

	Transform& transform = entity->getComponent<Transform>();
	BoxCollider& collider = entity->getComponent<BoxCollider>();

	double directionX, directionY, directionZ, scaleX, scaleY, scaleZ, attackType, traceUser;

	wchar_t szTemp[MAX_BUF];
	ZeroMemory(szTemp, sizeof(wchar_t)*MAX_BUF);
	GetPrivateProfileString(dataName, L"directionX", L"0.0", szTemp, MAX_BUF, L"../iniFiles/AttackBox.ini");
	directionX = _ttof(szTemp);

	ZeroMemory(szTemp, sizeof(wchar_t)*MAX_BUF);
	GetPrivateProfileString(dataName, L"directionY", L"0.0", szTemp, MAX_BUF, L"../iniFiles/AttackBox.ini");
	directionY = _ttof(szTemp);

	ZeroMemory(szTemp, sizeof(wchar_t)*MAX_BUF);
	GetPrivateProfileString(dataName, L"directionZ", L"0.0", szTemp, MAX_BUF, L"../iniFiles/AttackBox.ini");
	directionZ = _ttof(szTemp);

	ZeroMemory(szTemp, sizeof(wchar_t)*MAX_BUF);
	GetPrivateProfileString(dataName, L"scaleX", L"0.0", szTemp, MAX_BUF, L"../iniFiles/AttackBox.ini");
	scaleX = _ttof(szTemp);

	ZeroMemory(szTemp, sizeof(wchar_t)*MAX_BUF);
	GetPrivateProfileString(dataName, L"scaleY", L"0.0", szTemp, MAX_BUF, L"../iniFiles/AttackBox.ini");
	scaleY = _ttof(szTemp);

	ZeroMemory(szTemp, sizeof(wchar_t)*MAX_BUF);
	GetPrivateProfileString(dataName, L"scaleZ", L"0.0", szTemp, MAX_BUF, L"../iniFiles/AttackBox.ini");
	scaleZ = _ttof(szTemp);

	ZeroMemory(szTemp, sizeof(wchar_t)*MAX_BUF);
	GetPrivateProfileString(dataName, L"attackType", L"0.0", szTemp, MAX_BUF, L"../iniFiles/AttackBox.ini");
	attackType = _ttof(szTemp);

	ZeroMemory(szTemp, sizeof(wchar_t)*MAX_BUF);
	GetPrivateProfileString(dataName, L"traceUser", L"0.0", szTemp, MAX_BUF, L"../iniFiles/AttackBox.ini");
	traceUser = _ttof(szTemp);

	name_ = dataName;

	if (!userAnim.getIsRight())
		directionX *= -1.f;

	direction_ = _vec3((float)directionX, (float)directionY, (float)directionZ);
	if (absolute_ == _vec3(0, 0, 0))
		transform.position_ = userTransform.position_ + direction_;
	else
		transform.position_ = absolute_;
	collider.transform_.scale_ = { (float)scaleX,(float)scaleY,(float)scaleZ };
	
	if (userEntity->getType() == Entity::ENTITYTYPE::PLAYER)
		user_ = USER::PLAYER;
	else if(userEntity->getType() == Entity::ENTITYTYPE::ENEMY|| userEntity->getType() == Entity::ENTITYTYPE::ENEMYEFFECT)
		user_ = USER::ENEMY;
	else
		user_ = USER::ETC;


	physicalDamage_ = userStatus.physicalAttack_;
	magicalDamage_ = userStatus.magicalAttack_;
	if (nullptr != skillName)
	{
		//스킬 썼을경우
		if (userEntity->hasComponent<Skill>())
		{
			Skill& skill = userEntity->getComponent<Skill>();
			bool isPercent = skill.getIsPercent(skillName);
			float damageValue = skill.getDamageValue(skillName);

			if (isPercent)
			{
				physicalDamage_ *= damageValue;
				magicalDamage_ *= damageValue;
			}
			else
			{
				physicalDamage_ += damageValue;
				magicalDamage_ += damageValue;
			}
		}
	}
	
	if (userEntity->hasComponent<Status>())
	{
		if (userEntity->getComponent<Status>().isAttackUp_)
		{
			physicalDamage_ *= 2.f;
			magicalDamage_ *= 2.f;
		}
	}


	if(1==traceUser)
		userEntity_ = userEntity;

	if (0 == attackType)
	{
		attackType_ = ATTACKTYPE::HIT;
	}
	else if (1 == attackType)
	{
		attackType_ = ATTACKTYPE::DOWN;
	}
	else if (2 == attackType)
	{
		attackType_ = ATTACKTYPE::STUN;
	}

	activate_ = true;
}

void AttackBox::deactivate()
{
	Transform& transform = entity->getComponent<Transform>();
	BoxCollider& collider = entity->getComponent<BoxCollider>();

	userEntity_ = nullptr;
	transform.position_ = { -10000.f, -10000.f, -10000.f };
	collider.transform_.scale_ = { 0.f,0.f,0.f };
	alreadyCollideEntities_.clear();
	isHit_ = false;
	activate_ = false;
}

_vec3 AttackBox::getCollideEntityPosition()
{
	if (alreadyCollideEntities_.empty())
		return _vec3(-10000.f, -10000.f, -10000.f);

	for (auto& collideEntity : alreadyCollideEntities_)
	{
		if (collideEntity.expired())
			continue;
		if (!collideEntity.lock()->hasComponent<Transform>())
			continue;



		Transform& transform = collideEntity.lock()->getComponent<Transform>();
		return transform.position_;

	}
	return _vec3(-10000.f, -10000.f, -10000.f);
}
//
//void AttackBox::sendAttackBoxData()
//{
//#ifdef _DEBUG
//	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "Entity must need Transform component");
//#endif
//	Transform& transform = entity->getComponent<Transform>();
//	unique_ptr<UdpAttackObject> attackObjectData = make_unique<UdpAttackObject>();
//	int userIDN, entityNumber;
//	Entity::ENTITYTYPE entityType;
//	entity->getEntityNetworkInfo(userIDN, entityNumber, entityType);
//
//
//	attackObjectData->objectType_ = 100;
//
//	attackObjectData->userIDN_ = userIDN;
//	attackObjectData->objectNumber_ = entityNumber;
//	attackObjectData->subType_ = 0;
//	attackObjectData->attackerObjectType_ = (int)attackType_;
//	attackObjectData->attackerType_ = (int)user_;
//	attackObjectData->pX_ = transform.position_.x;
//	attackObjectData->pY_ = transform.position_.y;
//	attackObjectData->pZ_ = transform.position_.z;
//	attackObjectData->sizeX_ = transform.scale_.x;
//	attackObjectData->sizeY_ = transform.scale_.y;
//	attackObjectData->sizeZ_ = transform.scale_.z;
//	attackObjectData->pDamage_ = physicalDamage_;
//	attackObjectData->mDamage_ = magicalDamage_;
//
//	if(activate_)	
//		attackObjectData->isAttacking_ = true;
//	else
//		attackObjectData->isAttacking_ = false;
//
//	NetworkManager::getInstance()->thisUser_.udpDataList_.push_back(move(attackObjectData));
//}

void AttackBox::initialize()
{
	entity->addComponent<Transform>(_vec3(-10000.f, -10000.f, -10000.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	entity->addComponent<BoxCollider>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(100.f, 100.f, 100.f));

	string playSound[] = {
		"../resource/NumberUi/sound/fighter/bgloveb_hit_01.ogg", 
		"../resource/NumberUi/sound/fighter/bgloveb_hit_02.ogg",
		"../resource/NumberUi/sound/fighter/bglovec_hit.ogg",

	};

	entity->addComponent<Sound>().CreateEffectSound(_countof(playSound), playSound);

	entity->getComponent<BoxCollider>().bindColliderFunction(
		bind(&AttackBox::enterCollider, this, placeholders::_1),
		bind(&AttackBox::stayCollider, this, placeholders::_1),
		bind(&AttackBox::exitCollider, this, placeholders::_1));
}

void AttackBox::update()
{
	//sendAttackBoxData();


	if (nullptr == userEntity_)
		return;

	Transform& transform = entity->getComponent<Transform>();
	Transform& userTransform = userEntity_->getComponent<Transform>();

	if(absolute_== _vec3(0, 0, 0))
		transform.position_ = userTransform.position_ + direction_;
	else
		transform.position_ = absolute_;

	//activate면 서버에 계속 메시지 보냄
	
}

void AttackBox::lateUpdate()
{
}

void AttackBox::render()
{
}

void AttackBox::release()
{
}

void AttackBox::enterCollider(Entity* colliderEntity)
{
	if (!(colliderEntity->hasComponent<StateMachine>() && colliderEntity->hasComponent<Status>() &&
		colliderEntity->hasComponent<Rigidbody>() && colliderEntity->hasComponent<Transform>() &&
		colliderEntity->hasComponent<AtlasAnimation>()))
		return;
	for (auto& alreadyCollideEntity : alreadyCollideEntities_)
	{
		if (alreadyCollideEntity.expired())
			return;
		//이미 충돌한 객체면 리턴
		if (alreadyCollideEntity.lock().get() == colliderEntity)
			return;
	}



	bool isRightEntity = false; //올바른 엔티티인가 체크
	//충돌처리
	if (USER::PLAYER == user_)
	{
		//플레이어의 어택박스가 적과 충돌
		if (Entity::ENTITYTYPE::ENEMY == colliderEntity->getType())
		{
			isRightEntity = true;
		}
	}
	else if (USER::ENEMY == user_)
	{
		//적 어택박스가 플레이어와 충돌
		if (Entity::ENTITYTYPE::PLAYER == colliderEntity->getType())
		{
			isRightEntity = true;
		}
	}
	else
	{
		//그 외 소유의 어택박스가 오브젝트들과 충돌
		isRightEntity = true;
	}

	if (isRightEntity)
	{

#ifdef _DEBUG
		ASSERT_MESSAGE_NULLRETURN(colliderEntity->hasComponent<StateMachine>(), "collider Entity must have StateMachine Component");
		ASSERT_MESSAGE_NULLRETURN(colliderEntity->hasComponent<Status>(), "collider Entity must have Status Component");
		ASSERT_MESSAGE_NULLRETURN(colliderEntity->hasComponent<Rigidbody>(), "collider Entity must have Rigidbody Component");
		ASSERT_MESSAGE_NULLRETURN(colliderEntity->hasComponent<Transform>(), "collider Entity must have Transform Component");
		ASSERT_MESSAGE_NULLRETURN(colliderEntity->hasComponent<AtlasAnimation>(), "collider Entity must have AtlasAnimation Component");

#endif
	
		Status& status = colliderEntity->getComponent<Status>();
		Transform& transform = colliderEntity->getComponent<Transform>();
		BoxCollider& collider = colliderEntity->getComponent<BoxCollider>();
		
		_vec3 centerPosition = collider.transform_.position_ + transform.position_;
		shared_ptr<Entity> hitEffect;
		if (ATTACKTYPE::HIT == attackType_)
		{
			for (int i = 0; i < isMultiHit_; i++)
			{
				//데미지

				float totalDamage;

				totalDamage = (physicalDamage_ + magicalDamage_);
				int ind = (rand() % 50) % 100;
				totalDamage = totalDamage  + totalDamage * (float)ind;


				if (name_ == L"shine")
					totalDamage *= 12.f;

				float critical = rand() % 2;
				if (critical == 1)
					critical = 0.5f;
				
				status.damaged(totalDamage*critical, 0, entity);


				
				// 폰트

				if (colliderEntity->getType() == Entity::ENTITYTYPE::PLAYER)
					GameManager::getInstance()->makeDamageFont(DNFUI::UItype::Dnum0,totalDamage, transform.position_ + _vec3(0.f, 100.f, 0.f));
				else
				{


					if (name_ == L"shine")
						status.DamageFont(totalDamage, i, critical,1 );
						//hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/hit/shine3");
					else if (name_ == L"bigsurigum")
						status.DamageFont(totalDamage, i, critical,2 );
						//hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/maplechar/bigsurigum/hiteffect");

					else
						status.DamageFont(totalDamage, i, critical,0 );
					//	hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/hit/knockSmall");


					
				
		/*			if (name_ == L"shine")
						hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/hit/shine3");
					else if (name_ == L"bigsurigum")
						hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/maplechar/bigsurigum/hiteffect");

					else
						hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/hit/knockSmall");

					hitEffect->getComponent<CommonEffect>().setEffect(centerPosition + _vec3(0.f, 0.f, -1.f), 0.f, 1.f);*/

				}
			}
			
			
			/*if (rand() % 2 == 0)
				entity->getComponent<Sound>().PlaySoundEffect(0);
			else
				entity->getComponent<Sound>().PlaySoundEffect(1);*/
		}
		else if (ATTACKTYPE::DOWN == attackType_)
		{
			status.downed(physicalDamage_, magicalDamage_, entity);
			hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/hit/knockLarge");
			hitEffect->getComponent<CommonEffect>().setEffect(centerPosition, 0.f, 1.f);
			entity->getComponent<Sound>().PlaySoundEffect(2);
		}
		else if (ATTACKTYPE::STUN == attackType_)
		{
			status.stunned(physicalDamage_, magicalDamage_, entity);
			hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/hit/knockLarge");
			hitEffect->getComponent<CommonEffect>().setEffect(centerPosition, 0.f, 1.f);

		}



		isHit_ = true;

		shared_ptr<Entity> entity = EntityManager::getInstance()->findEntityWithPointer(colliderEntity);

		if(nullptr!=entity.get())
			alreadyCollideEntities_.emplace_back(entity);

	}
}

void AttackBox::stayCollider(Entity* colliderEntity)
{
//	if (!(colliderEntity->hasComponent<StateMachine>() && colliderEntity->hasComponent<Status>() &&
//		colliderEntity->hasComponent<Rigidbody>() && colliderEntity->hasComponent<Transform>() &&
//		colliderEntity->hasComponent<AtlasAnimation>()))
//		return;
//	for (auto& alreadyCollideEntity : alreadyCollideEntities_)
//	{
//		if (alreadyCollideEntity.expired())
//			return;
//		//이미 충돌한 객체면 리턴
//		if (alreadyCollideEntity.lock().get() == colliderEntity)
//			return;
//	}
//
//
//
//	bool isRightEntity = false; //올바른 엔티티인가 체크
//	//충돌처리
//	if (USER::PLAYER == user_)
//	{
//		//플레이어의 어택박스가 적과 충돌
//		if (Entity::ENTITYTYPE::ENEMY == colliderEntity->getType())
//		{
//			isRightEntity = true;
//		}
//	}
//	else if (USER::ENEMY == user_)
//	{
//		//적 어택박스가 플레이어와 충돌
//		if (Entity::ENTITYTYPE::PLAYER == colliderEntity->getType())
//		{
//			isRightEntity = true;
//		}
//	}
//	else
//	{
//		//그 외 소유의 어택박스가 오브젝트들과 충돌
//		isRightEntity = true;
//	}
//
//	if (isRightEntity)
//	{
//
//#ifdef _DEBUG
//		ASSERT_MESSAGE_NULLRETURN(colliderEntity->hasComponent<StateMachine>(), "collider Entity must have StateMachine Component");
//		ASSERT_MESSAGE_NULLRETURN(colliderEntity->hasComponent<Status>(), "collider Entity must have Status Component");
//		ASSERT_MESSAGE_NULLRETURN(colliderEntity->hasComponent<Rigidbody>(), "collider Entity must have Rigidbody Component");
//		ASSERT_MESSAGE_NULLRETURN(colliderEntity->hasComponent<Transform>(), "collider Entity must have Transform Component");
//		ASSERT_MESSAGE_NULLRETURN(colliderEntity->hasComponent<AtlasAnimation>(), "collider Entity must have AtlasAnimation Component");
//
//#endif
//
//		//StateMachine& stateMachine = colliderEntity->getComponent<StateMachine>();
//		Status& status = colliderEntity->getComponent<Status>();
//		Transform& transform = colliderEntity->getComponent<Transform>();
//		BoxCollider& collider = colliderEntity->getComponent<BoxCollider>();
//
//		_vec3 centerPosition = collider.transform_.position_ + transform.position_;
//		shared_ptr<Entity> hitEffect;
//
//
//		if (ATTACKTYPE::HIT == attackType_)
//		{
//			status.damaged(physicalDamage_, magicalDamage_, entity);
//			hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/hit/knockSmall");
//			hitEffect->getComponent<CommonEffect>().setEffect(centerPosition, 0.f, 1.f);
//
//			if(rand()%2==0)
//				entity->getComponent<Sound>().PlaySoundEffect(0);
//			else
//				entity->getComponent<Sound>().PlaySoundEffect(1);
//
//		}
//		else if (ATTACKTYPE::DOWN == attackType_)
//		{
//			status.downed(physicalDamage_, magicalDamage_, entity);
//			hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/hit/knockLarge");
//			hitEffect->getComponent<CommonEffect>().setEffect(centerPosition, 0.f, 1.f);
//			entity->getComponent<Sound>().PlaySoundEffect(2);
//
//		}
//		else if (ATTACKTYPE::STUN == attackType_)
//		{
//			status.stunned(physicalDamage_, magicalDamage_, entity);
//			hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/hit/knockLarge");
//			hitEffect->getComponent<CommonEffect>().setEffect(centerPosition, 0.f, 1.f);
//
//		}
//
//		if (colliderEntity->getType() == Entity::ENTITYTYPE::PLAYER)
//			GameManager::getInstance()->makeDamageFont(physicalDamage_ + magicalDamage_, transform.position_ + _vec3(0.f, 100.f, 0.f));
//		else
//			GameManager::getInstance()->makeEnemyFont(physicalDamage_ + magicalDamage_, transform.position_ + _vec3(0.f, 100.f, 0.f));
//
//
//		isHit_ = true;
//		shared_ptr<Entity> entity = EntityManager::getInstance()->findEntityWithPointer(colliderEntity);
//
//		if (nullptr != entity.get())
//			alreadyCollideEntities_.emplace_back(entity);
//
//
//	}
}

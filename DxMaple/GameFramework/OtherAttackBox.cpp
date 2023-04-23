#include "stdafx.h"
#include "OtherAttackBox.h"

#include "GameManager.h"

OtherAttackBox::OtherAttackBox(USER userType, ATTACKTYPE attackType, _vec3 position, _vec3 size, double physicalDamage, double magicalDamage)
	:user_(userType),attackType_(attackType),initPosition_(position),initSize_(size),physicalDamage_(physicalDamage),magicalDamage_(magicalDamage)
{
}

OtherAttackBox::~OtherAttackBox()
{
}

void OtherAttackBox::initialize()
{
	entity->addComponent<Transform>(initPosition_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	entity->addComponent<BoxCollider>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), initSize_);


	entity->getComponent<BoxCollider>().bindColliderFunction(
		bind(&OtherAttackBox::enterCollider, this, placeholders::_1),
		bind(&OtherAttackBox::stayCollider, this, placeholders::_1),
		bind(&OtherAttackBox::exitCollider, this, placeholders::_1));

	entity->getComponent<Transform>().isInterpolate_ = true;

}

void OtherAttackBox::update()
{
}

void OtherAttackBox::lateUpdate()
{
}

void OtherAttackBox::render()
{
}

void OtherAttackBox::release()
{
}

void OtherAttackBox::updatePosition(_vec3 position)
{
#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "Attackbox must need Transform component");
#endif
	Transform& transform = entity->getComponent<Transform>();
	transform.position_ = position;
}

void OtherAttackBox::enterCollider(Entity * colliderEntity)
{
	if (!(colliderEntity->hasComponent<StateMachine>() && colliderEntity->hasComponent<Status>() &&
		colliderEntity->hasComponent<Rigidbody>() && colliderEntity->hasComponent<Transform>() &&
		colliderEntity->hasComponent<AtlasAnimation>()))
		return;
	for (auto& alreadyCollideEntity : alreadyCollideEntities_)
	{
		//이미 충돌한 객체면 리턴
		if (alreadyCollideEntity == colliderEntity)
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

		shared_ptr<Entity> hitEffect;
		_vec3 centerPosition = collider.transform_.position_ + transform.position_;


		if (ATTACKTYPE::HIT == attackType_)
		{
			status.damaged(physicalDamage_, magicalDamage_, entity);
			hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/hit/knockSmall");
			hitEffect->getComponent<CommonEffect>().setEffect(centerPosition, 0.f, 1.f);

		}
		else if (ATTACKTYPE::DOWN == attackType_)
		{
			status.downed(physicalDamage_, magicalDamage_, entity);
			hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/hit/knockLarge");
			hitEffect->getComponent<CommonEffect>().setEffect(centerPosition, 0.f, 1.f);

		}
		else if (ATTACKTYPE::STUN == attackType_)
		{
			status.stunned(physicalDamage_, magicalDamage_, entity);
			hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/hit/knockLarge");
			hitEffect->getComponent<CommonEffect>().setEffect(centerPosition, 0.f, 1.f);

		}

		isHit_ = true;

		alreadyCollideEntities_.emplace_back(colliderEntity);

	}
}

void OtherAttackBox::stayCollider(Entity * colliderEntity)
{
	if (!(colliderEntity->hasComponent<StateMachine>() && colliderEntity->hasComponent<Status>() &&
		colliderEntity->hasComponent<Rigidbody>() && colliderEntity->hasComponent<Transform>() &&
		colliderEntity->hasComponent<AtlasAnimation>()))
		return;
	for (auto& alreadyCollideEntity : alreadyCollideEntities_)
	{
		//이미 충돌한 객체면 리턴
		if (alreadyCollideEntity == colliderEntity)
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

		shared_ptr<Entity> hitEffect;
		_vec3 centerPosition = collider.transform_.position_ + transform.position_;


		if (ATTACKTYPE::HIT == attackType_)
		{
			status.damaged(physicalDamage_, magicalDamage_, entity);
			hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/hit/knockSmall");
			hitEffect->getComponent<CommonEffect>().setEffect(centerPosition, 0.f, 1.f);

		}
		else if (ATTACKTYPE::DOWN == attackType_)
		{
			status.downed(physicalDamage_, magicalDamage_, entity);
			hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/hit/knockLarge");
			hitEffect->getComponent<CommonEffect>().setEffect(centerPosition, 0.f, 1.f);

		}
		else if (ATTACKTYPE::STUN == attackType_)
		{
			status.stunned(physicalDamage_, magicalDamage_, entity);
			hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/hit/knockLarge");
			hitEffect->getComponent<CommonEffect>().setEffect(centerPosition, 0.f, 1.f);

		}

		isHit_ = true;
		alreadyCollideEntities_.emplace_back(colliderEntity);


	}
}

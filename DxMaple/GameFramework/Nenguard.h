#pragma once
#include "MonoBehaviour.h"
class Nenguard :
	public MonoBehaviour
{

public:
	
	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
	void getDamage(float damage);
	shared_ptr<Entity> getHitBox() { return hitbox_; }
	void setAttackEnd() { isAttacking = false; }
	void setDirection();
//private:
	//void setEffectData();
public:


	//void enterCollider(Entity* colliderEntity)
	//{

	//	int a;
	//	a = 3;

	//	if (colliderEntity->getName() == L"SmallCircle")
	//	{
	//		trapHitted = false;
	//	}

	//	/*	if (colliderEntity->getTag() == L"trap" && trapHitted)
	//		{
	//			getDamage(3.f);

	//		}*/
	//}

	//void stayCollider(Entity* colliderEntity)
	//{
	//	int a;
	//	a = 3;

	//	/*if (colliderEntity->getName() == L"SmallCircle")
	//	{
	//		trapHitted = false;
	//	}*/

	//	if (colliderEntity->getType() == Entity::ENTITYTYPE::TRAP && trapHitted)
	//	{
	//		getDamage(3.f);

	//	}


	//}

	//void exitCollider(Entity* colliderEntity)
	//{
	//	int a;
	//	a = 3;

	//	if (colliderEntity->getName() == L"SmallCircle")
	//	{
	//		//ASSERT_MESSAGE(0, "aa");
	//		trapHitted = true;
	//	}
	//}

//private:
//	void Attack();
private:
	bool moving = false;
	bool operation = false;
	bool trapHitted = true;
	bool isAttacking = false;
	shared_ptr<Entity> hitbox_;
	wstring atlasPath_;
};


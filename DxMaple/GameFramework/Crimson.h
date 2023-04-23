#pragma once
#include "MonoBehaviour.h"
class Crimson :
	public MonoBehaviour
{
public:
	Crimson(_vec3 pos) { position_ = pos; }
	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;

	shared_ptr<Entity> getHitBox() { return hitbox_; }
	void Appear();

public:

	void getDamaged(Entity* attackboxEntity);
	void getDowned(Entity* attackboxEntity);

	shared_ptr<Entity> getAttackBox() { return attackBox_.lock(); }
	void enterCollider(Entity* colliderEntity)
	{


		if (colliderEntity->getName() == L"SmallCircle")
		{
			trapHitted_ = false;
		}


		if (colliderEntity->getType() == Entity::ENTITYTYPE::TRAP && trapHitted_)
		{

			entity->getComponent<Status>().hp_ -= 10000.f;
			getDamaged(colliderEntity);
		}
	}

	void stayCollider(Entity* colliderEntity)
	{


		if (colliderEntity->getType() == Entity::ENTITYTYPE::ENEMY)
		{

			Rigidbody& rigidbody= entity->getComponent<Rigidbody>();
				_vec3 direction;
			//오른쪽에서 온 공격이면 왼쪽으로튕김
			if (entity->getComponent<Transform>().position_.x > colliderEntity->getComponent<Transform>().position_.x)
				direction = { 1.f, 1.f, 0.f };
			else
				direction = { -1.f, -1.f, 0.f };

			rigidbody.setForce((rigidbody.direction_ + direction) * ATTACK_ACCEL);
		}


	}

	void exitCollider(Entity* colliderEntity)
	{

		if (colliderEntity->getName() == L"SmallCircle")
		{

			trapHitted_ = true;
		}
	}
private:
	void sendMonsterData();

private:
	bool operation_ = false;
	bool trapHitted_ = true;
	float attackCoolTime_;
	float skillCoolTime_=6.f;

	bool isAttacking_ = false;
	bool isAwake_ = false;
	bool isLife_ = true;
	float dieTime_;

	shared_ptr<Entity> hitbox_;
	weak_ptr<Entity> attackBox_;


	_vec3 position_;

};


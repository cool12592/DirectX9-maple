#pragma once
#include "MonoBehaviour.h"
class OtherAttackBox :
	public MonoBehaviour
{
public:
	enum class ATTACKTYPE { HIT = 0, DOWN, STUN };
	enum class USER { PLAYER = 0, ENEMY, ETC };
public:
	OtherAttackBox(USER userType,ATTACKTYPE attackType,_vec3 position,_vec3 size,double physicalDamage,double magicalDamage);
	virtual ~OtherAttackBox();
	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;

	void updatePosition(_vec3 position);
public:
	void enterCollider(Entity* colliderEntity);
	void stayCollider(Entity* colliderEntity);

	void exitCollider(Entity* colliderEntity) {}

private:
	vector<Entity*> alreadyCollideEntities_;
	USER user_ = USER::ETC;
	ATTACKTYPE attackType_ = ATTACKTYPE::HIT;
	_vec3 initPosition_;
	_vec3 initSize_;
	double physicalDamage_ = 0.f;
	double magicalDamage_ = 0.f;

	bool isHit_ = false; //누군가 맞음

};


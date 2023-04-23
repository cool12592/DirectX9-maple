#pragma once
#include "MonoBehaviour.h"
class HornTailLeft :
	public MonoBehaviour
{
public:
	HornTailLeft() {}
	HornTailLeft(wstring type) { type_ = type; }

	// MonoBehaviour��(��) ���� ��ӵ�
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
	void getDamage(float damage);
	shared_ptr<Entity> getHitBox() { return hitbox_; }
	void setAttackEnd() { bAttackTerm = true; fAttackTerm = 0.f; }
	void setDirection();
public:
	void getDamaged(Entity* attackboxEntity);
	void getDowned(Entity* attackboxEntity);
	void enterCollider(Entity* colliderEntity)
	{
		int a=0;
	}

	void stayCollider(Entity* colliderEntity)
	{
		

	}

	void exitCollider(Entity* colliderEntity)
	{
	
	}
	shared_ptr<Entity> getAttackBox() { return attackBox_.lock(); }
	vector<_vec3>getIcePosition() { return icePosition_; }
private:
	void Attack();
	bool bAttackTerm = false;
	float fAttackTerm;
	void sendMonsterData();
private:
	int stateCheck = -1;

	bool moving = false;
	bool operation = true;
	bool trapHitted = true;
	bool isAttacking = false;
	shared_ptr<Entity> hitbox_;
	shared_ptr<Entity> nenguard;
	//float skillCoolTime =10000.f;
	//float skillTimeCount=0.f;
	int skillNumber;
	int ind;
	shared_ptr<Entity>	circleCenter;
	shared_ptr<Entity>	shadow;
	vector<pair<float, float>> skillcooltime = { make_pair(25.f,45.f),make_pair(2.f,35.f),make_pair(2.f,35.f),make_pair(2.f,35.f) };

	vector<int> readyskill;

	
	void skillReset();

	bool onVanish_ = false;
	float vanishAlpha_;
	float vanishSpeed_ = 0.f;
	shared_ptr<Entity> HornTailLeftShadow;
	bool isLife_ = true;
	float dieTime_ = 0.f;
	float nenHP;
	wstring type_;

	weak_ptr<Entity> attackBox_;

	vector<_vec3> icePosition_;
};

#pragma once
#include "MonoBehaviour.h"
class HornTail :
	public MonoBehaviour
{
public:
	HornTail() {}
	HornTail(wstring type) { type_ = type; }

	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
	void getDamage(float damage);
	shared_ptr<Entity> getHitBox() { return hitbox_; }
	void setAttackEnd() { bAttackTerm = true; fAttackTerm = 0.f; }
	void setDirection();
	weak_ptr<Entity> getRightHead() { return LeftHead.lock(); }
	weak_ptr<Entity> getLeftHead() { return RightHead.lock(); }
	weak_ptr<Entity> getBody() { return body_.lock(); }


	shared_ptr<Entity> getAttackBox() { return attackBox_.lock(); }
	vector<_vec3>getFirePosition() { return firePosition_; }
	vector<_vec3>getIcePosition() { return icePosition_; }

public:
	int page_ = 1;
	float HornTail_totalHP;

	void getDamaged(Entity* attackboxEntity);
	void getDowned(Entity* attackboxEntity);
	void enterCollider(Entity* colliderEntity)
	{

	
	}

	void stayCollider(Entity* colliderEntity)
	{
	
	}

	void exitCollider(Entity* colliderEntity)
	{
		
	}

private:
	void Attack();
	bool bAttackTerm = false;
	float fAttackTerm=0.f;
	float bodyAttackTerm=0.f;
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
private:

	bool onVanish_ = false;
	float vanishAlpha_;
	float vanishSpeed_ = 0.f;
	shared_ptr<Entity> HornTailShadow;
	bool isLife_ = true;
	float dieTime_ = 0.f;
	float nenHP;
	wstring type_;

	weak_ptr<Entity> body_;
	weak_ptr<Entity> RightHead;
	weak_ptr<Entity> LeftHead;
	weak_ptr<Entity> attackBox_;
	vector<_vec3> firePosition_;
	vector<_vec3> icePosition_;





	shared_ptr<Entity> horntail;//혼테일 서머너가 소환함

	shared_ptr<Entity> hp_UI;
	shared_ptr<Entity> backHPui;
	shared_ptr<Entity> icon_ui;
};


#pragma once
#include "MonoBehaviour.h"
class AttackBox :
	public MonoBehaviour
{
public:
	enum class ATTACKTYPE { HIT = 0, DOWN, STUN };
	enum class USER { PLAYER = 0, ENEMY, ETC };
public:
	AttackBox() { }
	virtual ~AttackBox() {}

	//이거말고
	void activateAttackBox(_vec3 position, _vec3 scale, USER user, float physicalDamage = 0.f, float magicalDamage = 0.f);

	//이거 쓰세요
	void activateAttackBox(const wchar_t* dataName, Entity* userEntity, const wchar_t* skillName = nullptr);
	void deactivate();

	void multiplyPhysicalDamage(double multiplier) { physicalDamage_ *= multiplier; }
	void multiplyMagicalDamage(double multiplier) { magicalDamage_ *= multiplier; }

	bool checkHit() const { return isHit_; }
	_vec3 getCollideEntityPosition();

	vector<weak_ptr<Entity>>* getCollideEntities() { return &alreadyCollideEntities_; }

	void multiHit(int multiplier) { isMultiHit_ = multiplier; }
	void setAbsoluteCoordinates(_vec3 absolute) { absolute_ = absolute; }
//private:
	//void sendAttackBoxData();
public:
	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
public:
	void enterCollider(Entity* colliderEntity);
	void stayCollider(Entity* colliderEntity);

	void exitCollider(Entity* colliderEntity)
	{

	}
private:
	vector<weak_ptr<Entity>> alreadyCollideEntities_;
	USER user_ = USER::ETC;
	ATTACKTYPE attackType_ = ATTACKTYPE::HIT;
	Entity* userEntity_ = nullptr;
	_vec3 direction_ = { 0.f,0.f,0.f };

	double physicalDamage_ = 0.f;
	double magicalDamage_ = 0.f;



	bool isHit_ = false; //누군가 맞음
	bool activate_ = false;
	int isMultiHit_ = 1;
	_vec3 absolute_=_vec3(0,0,0);

	wstring name_;

};


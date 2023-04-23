#pragma once
#include "MonoBehaviour.h"

class Status;
class PlayerController :
	public MonoBehaviour
{
public:
	PlayerController();
	PlayerController(wstring className, _vec3 position);
	virtual ~PlayerController();

	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
	void equip(int type);

public:
	void setWeaponFront(shared_ptr<Entity>& weaponEntity) { weaponFront_ = weaponEntity; }
	void setWeaponBack(shared_ptr<Entity>& weaponEntity) { weaponBack_ = weaponEntity; }
	shared_ptr<Entity> getAttackBox() { return attackBox_.lock(); }


	void updateWeaponPositionAndAnimation();
	void setNotTrap(bool trap) { trapHitted_ = trap; }
	void setReCameraSetting();
	

private:
	void OnMove();
	void OnAttack();
	void OnJump();
	void OnSkill();
	void commandInput();

	void sendPlayerData();
	void checkExpiredAndMakeAttackbox();
	void checkHostSceneChanged();


public:
	void getDamaged(Entity* attackboxEntity);
	void getDowned(Entity* attackboxEntity);
	void getStunned(Entity* attackboxEntity);

	void enterCollider(Entity* colliderEntity);

	void stayCollider(Entity* colliderEntity);
	

	void exitCollider(Entity* colliderEntity)
	{

	
	}
	wstring playerSurigumName_ = L"surigum";
private:
	weak_ptr<Entity> weaponFront_;
	weak_ptr<Entity> weaponBack_;
	wstring	className_;
	_vec3 initPosition_;
	bool trapHitted_ = false;
	
	weak_ptr<Entity> attackBox_;
	float invincibleTime_=0.f;


	bool shoot_ = false;
	float shootTimer_ = 0.f;
	int shootCount_ = 0;
	_vec3 surigumDir_=_vec3(0.f,0.f,0.f);
	_vec3 shadowSurigumDir_ = _vec3(0.f, 0.f, 0.f);

public:
	weak_ptr<Entity> targetBox_;
	int tempPastArea=0;
	weak_ptr<Entity> inventory_;
	bool alpha=false;
	bool invincibleTimer_=false;

	shared_ptr<Entity> usingWeaponUI;

	
	void AttackStart() { shoot_ = true;  shootTimer_ = 0.f; }

	RECT RT_;
	wstring text_;
	
};


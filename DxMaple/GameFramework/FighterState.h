#pragma once
#include "IState.h"


//namespace로 묶기
BEGIN(FighterState)
class Damaged :public IState
{
public:
	float tempTimer = 0.f;
	static Damaged instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;
	void stopEndTrigger(Entity* entity);

};

class Downed :public IState
{
public:
	static Downed instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;
	void stopEndTrigger(Entity* entity);

};
class Idle :public IState
{
public:
	static Idle instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

};

class Walk :public IState
{
public:
	static Walk instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

};

class Jump :public IState
{
public:
	static Jump instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

};

class Dash :public IState
{
public:
	static Dash instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;
private:
	float timer;
};


class Attack_1 :public IState
{
public:
	static Attack_1 instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTrigger(Entity* entity);

};

class Flash :public IState
{
public:
	static Flash instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTrigger(Entity* entity);

};

class Attack_2 :public IState
{
public:
	static Attack_2 instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTrigger(Entity* entity);

};

class Attack_3 :public IState
{
public:
	static Attack_3 instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTrigger(Entity* entity);

};

class Attack_4 :public IState
{
public:
	static Attack_4 instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;


};

class Attack_Dash :public IState
{
public:
	static Attack_Dash instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;
	void stopEndTrigger(Entity* entity);
};

class Attack_Jump :public IState
{
public:
	static Attack_Jump instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;
};

class HammerKick :public IState
{
public:
	static HammerKick instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	shared_ptr<Entity> effect;
	bool first = true;
};

class LowKick :public IState
{
public:
	static LowKick instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	Entity* getCloseEnemy(Entity* player);
	vector<weak_ptr<Entity>> alreadyHitEnemies;

	vector<shared_ptr<Entity>>* EnemyList;


};

class Hosinyeongeok :public IState
{
public:
	static Hosinyeongeok instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTrigger(Entity* entity);

};


class HoverStomp :public IState
{
public:
	static HoverStomp instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;
private:
	float timer;
	weak_ptr<Entity> effect;
};

class Boonggwon :public IState
{
public:
	static Boonggwon instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTrigger(Entity* entity);
private:
	bool effectCreated;
};

class Ganggwon :public IState
{
public:
	static Ganggwon instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;
};

class BoneCrusher :public IState
{
public:
	static BoneCrusher instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTrigger(Entity* entity);
	void stopEndTriggerReady(Entity* entity);
private:
	bool effectCreated;
};

class Jilpoonggak :public IState
{
public:
	static Jilpoonggak instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;
private:
	_vec3 direction;
	int rotateCount;
	weak_ptr<Entity> effect;
};

class RisingKnuckle :public IState
{
public:
	static RisingKnuckle instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;
	void stopEndTrigger(Entity* entity);
private:
	bool topReached;
	bool onGround;
	float timer;
};

class LighteningDance :public IState
{
public:
	static LighteningDance instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;
	Entity* getCloseEnemy(Entity* player);
private:
	int hitCount;
	float timer;
	bool effectCreated;
	float angle;
	vector<weak_ptr<Entity>> alreadyHitEnemies;
};


class Bitdrive :public IState
{
public:
	static Bitdrive instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;
	void stopEndTrigger(Entity* entity);
private:
	float timer;
	weak_ptr<Entity> effect;
	weak_ptr<Entity> effectDust;
};

class Chulsango :public IState
{
public:
	static Chulsango instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;
	void stopEndTrigger(Entity* entity);
};

class OneInchPunch :public IState
{
public:
	static OneInchPunch instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;
	void stopEndTrigger(Entity* entity);

	void lockDamageState();
	void lockHitEnemies(Entity* entity);
private:
	float timer;

	bool lockEnemy;
	vector<weak_ptr<Entity>> vecHitEnemies;
	_vec3 attackBoxPosition;
};

class PowerfulLowkick :public IState
{
public:
	static PowerfulLowkick instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;
	void stopEndTrigger(Entity* entity);
	void stopEndTriggerSecond(Entity* entity);

	void lockDamageState();
	void lockHitEnemies(Entity* entity);
	void zoomIn(Entity* entity);
private:
	float timer;
	bool initRight;

	weak_ptr<Entity> chargeEffect[9];
	weak_ptr<Entity> universeEffect;
	vector<weak_ptr<Entity>> vecHitEnemies;
	_vec3 attackBoxPosition;
};


class BackStep :public IState
{
public:
	static BackStep instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;
};

class QuickStanding :public IState
{
public:
	static QuickStanding instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTringger(Entity* entity);

};


class Rope :public IState
{
public:
	static Rope instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTringger(Entity* entity);

};



class KneelDown :public IState
{
public:
	static KneelDown instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTringger(Entity* entity);

};
END
	

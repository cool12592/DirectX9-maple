#pragma once
#include "IState.h"


//namespace로 묶기
BEGIN(CrimsonState)

class Idle :public IState
{
public:
	static Idle instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

};

class Move :public IState
{
public:
	static Move instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;


};




class Attack :public IState
{
public:
	static Attack instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTrigger(Entity* entity);
	bool first = true;
	shared_ptr<Entity> myBullet;
};

class Attack2 :public IState
{
public:
	static Attack2 instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTrigger(Entity* entity);

};

class BeHitted :public IState
{
public:
	static BeHitted instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTrigger(Entity* entity);

};

class BeHitted0 :public IState
{
public:
	static BeHitted0 instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTrigger(Entity* entity);

};

class Die :public IState
{
public:
	static Die instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTrigger(Entity* entity);

};
END


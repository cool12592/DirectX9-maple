#pragma once
#include "IState.h"


//namespace로 묶기
BEGIN(HornTailState)




class Idle :public IState
{
public:
	static Idle instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

};

class Attack1 :public IState
{
public:
	static Attack1 instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

};


class Attack2 :public IState
{
public:
	static Attack2 instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

};
class Die :public IState
{
public:
	static Die instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

};


class HornTailDie :public IState
{
public:
	static HornTailDie instance;
	// IState을(를) 통해 상속됨
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

};
END


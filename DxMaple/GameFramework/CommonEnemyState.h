#pragma once
#include "IState.h"


//namespace�� ����
BEGIN(CommonEnemyState)

class Idle :public IState
{
public:
	static Idle instance;
	// IState��(��) ���� ��ӵ�
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	float thinkTime = 0.f;
	float myTimer = 0.f;


};

class Move :public IState
{
public:
	static Move instance;
	// IState��(��) ���� ��ӵ�
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;
	float myTimer = 0.f;
	float endTime = 0.f;
	float  randomNum = 0.f;

};




class Attack :public IState
{
public:
	static Attack instance;
	// IState��(��) ���� ��ӵ�
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTrigger(Entity* entity);

};



class BeHitted :public IState
{
public:
	static BeHitted instance;
	// IState��(��) ���� ��ӵ�
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTrigger(Entity* entity);

};



class Die :public IState
{
public:
	static Die instance;
	// IState��(��) ���� ��ӵ�
	virtual void enter(Entity* entity) override;
	virtual void update(Entity* entity) override;
	virtual void exit(Entity* entity) override;

	void stopEndTrigger(Entity* entity);

};

END


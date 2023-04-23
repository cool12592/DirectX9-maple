#pragma once
#include "MonoBehaviour.h"
class CommonEnemy :
	public MonoBehaviour
{
public:
	CommonEnemy(wstring name) { name_ = name; }
	// MonoBehaviour��(��) ���� ��ӵ�
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;

	void getDamaged(Entity* attackboxEntity);


	void enterCollider(Entity* colliderEntity)
	{
	


	}

	void stayCollider(Entity* colliderEntity)
	{




	}

	void exitCollider(Entity* colliderEntity)
	{


	}

	bool isLife_ = true;
private:
	wstring name_;
	float myTimmer = 0.f;
	
	
};


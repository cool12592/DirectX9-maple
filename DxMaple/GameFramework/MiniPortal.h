#pragma once
#include "MonoBehaviour.h"
class MiniPortal :
    public MonoBehaviour
{
public:
	
	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;

	void playerTransmission();
public:
	void enterCollider(Entity* colliderEntity)
	{
		if (colliderEntity->getName() == L"player")
		{
			portalON = true;
		}
	}

	void stayCollider(Entity* colliderEntity)
	{

	}

	void exitCollider(Entity* colliderEntity)
	{
		if (colliderEntity->getName() == L"player")
		{
			portalON = false;
		}
	}
	_vec3 destination_ = _vec3(0.f, 0.f, 0.f);
private:
	bool portalON = false;

};


#pragma once
#include "MonoBehaviour.h"
class Mouse :
	public MonoBehaviour
{
public:
	weak_ptr<Entity> getCollideEntity() { return collideEntity_; }

private:
	void updateMouseTransform();
	void onCheckCollider();


public:
	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
private:
	weak_ptr<Entity> collideEntity_;
	float timer_ = 0.f;
};


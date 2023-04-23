#pragma once
#include "ECS.h"
class InputManager;
class Ray :
	public Component
{
public:
	Ray();
	virtual ~Ray();
public:
	bool rayCastCollider2D(const COLLIDERRECT2D& colliderRect);

public:
	// Component을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
private:
	HRESULT updateRay();
public:
	_vec3 origin_;
	_vec3 direction_;


private:
	LPDIRECT3DDEVICE9 device_;
	InputManager* inputManager_;
};


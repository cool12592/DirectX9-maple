#pragma once
#include "ECS.h"
#include "TimeManager.h"
class Rigidbody :
	public Component
{
public:
	Rigidbody();
	virtual ~Rigidbody();

	void setMass(const float& mass) { mass_ = mass; }
	void setDrag(const float& drag) { drag_ = drag; }
	void setUseGravity(bool useGravity);
	void setForce(const _vec3& force);
	void addForce(const _vec3& force);

	float getCurrentSpeed() const;
	bool	getUseGravity()const { return useGravity_; }
public:
	// Component을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
private:
	void executeAccelation();
public:
	_vec3 direction_;
	_vec3 velocity_; //속도
	_vec3 accelation_; //가속
	float mass_; //무게
	float drag_; //마찰력?
	bool onGround_ = false;
	bool inRope_ = false;
	bool topRope_ = false;
	Entity* rbOBB_;
private:
	TimeManager* timeManager_;

	_vec3 gravityAccel = { 0.f,-3000.f,0.f };
	bool useGravity_; //중력 사용 여부


};


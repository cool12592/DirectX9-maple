#pragma once
#include "MapBasic.h"
class BounDary :
	public MapBasic
{
public:
	BounDary() {};
	~BounDary() {};
	BounDary(int type, _vec3 position) { type_ = type; position_ = position; scale_ = _vec3(100.f, 100.f, 100.f); }
	BounDary(int type, _vec3 position, _vec3 scale) {
		type_ = type; position_ = position; scale_ = scale;
	}
	virtual void initialize() override;
	virtual void update() override;
	
public:
	void enterCollider(Entity* colliderEntity);
	
	void stayCollider(Entity* colliderEntity);

	void exitCollider(Entity* colliderEntity)
	{

	
		if (colliderEntity->getName() != L"player" && colliderEntity->getType() != Entity::ENTITYTYPE::ENEMY)
			return;
		if (!colliderEntity->hasComponent<Rigidbody>())
			return;

		if (isOBB)
			return;

		Rigidbody& rb = colliderEntity->getComponent<Rigidbody>();
		if (type_ == 0)
			rb.onGround_ = false;

		
		else if (type_ == 1)
			rb.inRope_ = false;
				
			
		else if (type_ == 2)
			rb.topRope_ = false;
		
			
		
	
	}
	bool isOBB=false;
	int hill = 1;
private:
	int type_;
	_vec3 scale_ = _vec3(100.f, 100.f, 100.f);
	_vec3 position_=_vec3(0.f,0.f,0.f);
	shared_ptr<Entity> player_;
	float exitTimer=0.f;
	bool exitTime=false;

};

//0¿œπ› ∂•
//1 πÂ¡Ÿ
//2 ≈æπÂ¡Ÿ
//3 ø∑∫Æ

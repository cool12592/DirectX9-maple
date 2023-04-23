#include "stdafx.h"
#include "Rigidbody.h"
#include "Transform.h"
#include "BoxCollider.h"
Rigidbody::Rigidbody():velocity_(_vec3(0.f,0.f,0.f)),accelation_(_vec3(0.f, 0.f, 0.f)),mass_(0.f),drag_(0.1f),useGravity_(false),timeManager_(TimeManager::getInstance())
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::setUseGravity(bool useGravity)
{
	useGravity_ = useGravity;
	ZeroMemory(&velocity_, sizeof(_vec3));
	ZeroMemory(&accelation_, sizeof(_vec3));


}

void Rigidbody::setForce(const _vec3& force)
{
	if (fabs(force.y) > 0.f)
	{
		velocity_.y = force.y / mass_;
		//onGround_ = false;

	}
	velocity_.x = force.x / mass_;
	velocity_.z = force.z / mass_;

}

void Rigidbody::addForce(const _vec3& force)
{

	if (force.y !=0.f)
	{
		onGround_ = false;
	}
	velocity_ += force / mass_;
}


float Rigidbody::getCurrentSpeed() const
{
	return D3DXVec3Length(&velocity_);
}




void Rigidbody::initialize()
{
}

void Rigidbody::update()
{
#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "rigidbody needs transform component");
#endif
	Transform& transform = entity->getComponent<Transform>();



	transform.position_ += velocity_ * timeManager_->getDeltaTime();


	executeAccelation();

	velocity_ = ws::Math::clampVectorExceptY(velocity_ + accelation_ * timeManager_->getDeltaTime(), _vec3(0.f, 0.f, 0.f), velocity_);


	//velocity.y가0미만일때 엔티티가 그래비티on이고 땅을 안밝고있다면 계속 내려오게하면됨
	//근데 0미만이면 어차피 내려가는건 자동이니까 멈추는 조건만 주면됨





		//땅밟으면 정지 (땅위치에 고정) (안그러면 계속 낙하중)
	//땅은 colliderDetection에서 true해주고 
	// Boundary 에서 exit콜라이더에서 false해줌
		if (onGround_)
		{
		
			
			//transform.position_.y = Box.lastColliderPos + Box.transform_.scale_.y - 10.f;
			velocity_.y = 0.f;
			accelation_.y = 0.f;
			//onGround_ = true;
		}
		/*else
		{
			onGround_ = false;
		}*/

	

	

	if (D3DXVec3Length(&velocity_) < 0.01f)
	{
		ZeroMemory(&velocity_, sizeof(_vec3));
		ZeroMemory(&accelation_, sizeof(_vec3));
	}
		
}

void Rigidbody::lateUpdate()
{
}

void Rigidbody::render()
{
}

void Rigidbody::release()
{
}

void Rigidbody::executeAccelation()
{
	_vec3 dragAccel;
	float velocityValue = D3DXVec3Length(&velocity_);


	D3DXVec3Normalize(&dragAccel, &velocity_);
	dragAccel *= drag_ * mass_;
	dragAccel.y = 0.f;

	//Gravity 상태면 Y addforce를 했던 안했건 항상 낙하하고있음!!
	//단지 땅밝음상태에서 다 0  + 좌표고정으로 막아주고있던것!!
	//그러니 땅 밟음 상태가 풀리면 당연히 떨어지지
	if (useGravity_)
	{
		accelation_ -= dragAccel * timeManager_->getDeltaTime();
		if (!onGround_)
			accelation_ += gravityAccel * timeManager_->getDeltaTime();
			
		
		

	}
	else
		accelation_ -= dragAccel* timeManager_->getDeltaTime();
	
}



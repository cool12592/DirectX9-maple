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


	//velocity.y��0�̸��϶� ��ƼƼ�� �׷���Ƽon�̰� ���� �ȹ���ִٸ� ��� ���������ϸ��
	//�ٵ� 0�̸��̸� ������ �������°� �ڵ��̴ϱ� ���ߴ� ���Ǹ� �ָ��





		//�������� ���� (����ġ�� ����) (�ȱ׷��� ��� ������)
	//���� colliderDetection���� true���ְ� 
	// Boundary ���� exit�ݶ��̴����� false����
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

	//Gravity ���¸� Y addforce�� �ߴ� ���߰� �׻� �����ϰ�����!!
	//���� ���������¿��� �� 0  + ��ǥ�������� �����ְ��ִ���!!
	//�׷��� �� ���� ���°� Ǯ���� �翬�� ��������
	if (useGravity_)
	{
		accelation_ -= dragAccel * timeManager_->getDeltaTime();
		if (!onGround_)
			accelation_ += gravityAccel * timeManager_->getDeltaTime();
			
		
		

	}
	else
		accelation_ -= dragAccel* timeManager_->getDeltaTime();
	
}



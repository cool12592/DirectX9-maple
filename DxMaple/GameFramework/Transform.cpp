#include "stdafx.h"
#include "Transform.h"

#include "TimeManager.h"
Transform::Transform()
{
}

Transform::Transform(_vec3 position, _vec3 rotation, _vec3 scale)
	:position_(position),rotation_(rotation),scale_(scale),interPosition_(_vec3(0.f,0.f,0.f)),isInterpolate_(false)
{
	D3DXMatrixIdentity(&worldMatrix_);
}


Transform::~Transform()
{
}

void Transform::initialize()
{
}

void Transform::update()
{
	if (isInterpolate_)
	{
		float clampValue = clamp(TimeManager::getInstance()->getDeltaTime()*INTERPOLATE_SPEED, 0.f, 1.f);
		D3DXVec3Lerp(&position_, &position_, &interPosition_, clampValue);
	}
}

void Transform::lateUpdate()
{

		worldMatrix_ = calculateWorldmatrix(position_, rotation_, scale_);
		worldMatrix2D_ = ws::Math::calculateWorldMatrix2D(position_, rotation_, scale_);

}

void Transform::render()
{
}

void Transform::release()
{
}

_mat Transform::getParentPositionMatrix()
{
	_mat parentPositionMatrix;
	D3DXMatrixIdentity(&parentPositionMatrix);
	if (nullptr == parentMatrix_)
		return parentPositionMatrix;

	memcpy(parentPositionMatrix.m[3], (*parentMatrix_).m[3], sizeof(_vec3));
	return parentPositionMatrix;
}

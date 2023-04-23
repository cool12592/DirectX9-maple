#include "stdafx.h"
#include "Camera.h"
#include "Transform.h"
#include "TimeManager.h"
Camera::Camera(CAMERA_MODE cameraMode, _vec3 position, _vec3 direction, float screenWidth, float screenHeight, float fovy, float nearDistance, float farDistance)
	:cameraMode_(cameraMode),position_(position),direction_(*D3DXVec3Normalize(&direction,&direction)),screenWidth_(screenWidth),screenHeight_(screenHeight), fovy_(fovy),near_(nearDistance),far_(farDistance),deviceManager_(DeviceManager::getInstance()),onTrace_(false),onZoom_(false)
{
}

Camera::~Camera()
{
}

HRESULT Camera::setPosition(_vec3 position)
{
	position_ = position;
	atPosition_ = position_ + direction_;

	ASSERT_MESSAGE_RETURN(SUCCEEDED(deviceManager_->setViewSpace(position_, atPosition_, upDirection_)),"view space setting failed",E_FAIL);
	return S_OK;
}

HRESULT Camera::rotateAxis(AXIS_TYPE axisType, float angle)
{
	_mat matRotation;
	D3DXMatrixIdentity(&matRotation);
	switch (axisType)
	{
	case AXIS_TYPE::X_AXIS:
		D3DXMatrixRotationX(&matRotation, angle);
		break;
	case AXIS_TYPE::Y_AXIS:
		D3DXMatrixRotationY(&matRotation, angle);
		break;
	case AXIS_TYPE::Z_AXIS:
		D3DXMatrixRotationZ(&matRotation, angle);
		break;
	}
	D3DXVec3TransformNormal(&direction_, &direction_, &matRotation);
	atPosition_ = position_ + direction_;


	_vec3 rightDir;
	D3DXVec3Cross(&rightDir, &_vec3(0.f, 1.f, 0.f), &direction_);
	D3DXVec3Cross(&upDirection_, &direction_, &rightDir);

	deviceManager_->setViewSpace(position_, atPosition_, upDirection_);
	return S_OK;
}

HRESULT Camera::setCameraMode(CAMERA_MODE cameraMode, float nearDistance, float farDistance)
{
	return E_NOTIMPL;
}

void Camera::setOnTrace(float xLimit, float yLimit)
{
	onTrace_ = true;
	xLimit_ = xLimit;
	yLimit_ = yLimit;
}

void Camera::setOnLock(_vec2 leftLimit, _vec2 rightLimit)
{
	onLock_ = true;
	leftLimit_ = leftLimit;
	rightLimit_ = rightLimit;
}

void Camera::setOnZoomIn(_vec3 targetCameraPosition, float zoomMagnification, float zoomSpeed,float zoomDuration)
{
	onZoom_ = true;
	originalPosition_ = position_;
	originalScreenWidth_ = screenWidth_;
	originalScreenHeight_ = screenHeight_;

	targetPosition_ = targetCameraPosition;
	zoomScreenWidth_ = originalScreenWidth_ / zoomMagnification;
	zoomScreenHeight_ = originalScreenHeight_ / zoomMagnification;
	zoomSpeed_ = zoomSpeed;
	zoomDuration_ = zoomDuration;
	zoomTimer_ = 0.f;
	lerpValue = 0.f;

}

void Camera::traceEntity()
{
	if (!onTrace_)
		return;
#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "entity must need Transform component");
#endif
	Transform& transform = entity->getComponent<Transform>();

	float xPos2D = transform.position_.x;
	float yPos2D = transform.position_.y + transform.position_.z;

	float clampValue = clamp(TimeManager::getInstance()->getDeltaTime() * CAMERA_INTERPOLATE_SPEED, 0.f, 1.f);
	if (position_.x - xLimit_ >= xPos2D)
		position_.x = ws::Math::lerp(position_.x, xPos2D + xLimit_, clampValue);
	else if (position_.x + xLimit_ <= xPos2D)
		position_.x = ws::Math::lerp(position_.x, xPos2D - xLimit_, clampValue);

	if (position_.y - yLimit_ >= yPos2D)
		position_.y = ws::Math::lerp(position_.y, yPos2D + yLimit_, clampValue);
	else if (position_.y + yLimit_ <= yPos2D)
		position_.y = ws::Math::lerp(position_.y, yPos2D - yLimit_, clampValue);

}

void Camera::lockEntity()
{
	if (!onLock_)
		return;

	if (leftLimit_.x >= position_.x)
			position_.x= leftLimit_.x;
	 if (leftLimit_.y >= position_.y)
		 position_.y = leftLimit_.y;

	 if (rightLimit_.x <= position_.x)
		 position_.x = rightLimit_.x;
	 if (rightLimit_.y <=  position_.y)
		 position_.y = rightLimit_.y;

}

void Camera::zoom()
{
	if (!onZoom_)
		return;

	D3DXVec3Lerp(&position_, &originalPosition_, &targetPosition_, lerpValue);

	screenWidth_ = ws::Math::lerp(originalScreenWidth_, zoomScreenWidth_, lerpValue);
	screenHeight_ = ws::Math::lerp(originalScreenHeight_, zoomScreenHeight_, lerpValue);
	

	if (zoomTimer_ > zoomDuration_)
	{
		onZoom_ = false;
		position_ = originalPosition_;
		screenWidth_ = originalScreenWidth_;
		screenHeight_ = originalScreenHeight_;
	}
	lerpValue += TimeManager::getInstance()->getDeltaTime()*zoomSpeed_;
	zoomTimer_ += TimeManager::getInstance()->getDeltaTime();

	if (lerpValue > 1.f)
		lerpValue = 1.f;
}

void Camera::initialize()
{
#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(deviceManager_ != nullptr, "device manager is nullptr");
#endif
	atPosition_ = position_ + direction_;

	_vec3 rightDir;
	D3DXVec3Cross(&rightDir, &_vec3(0.f, 1.f, 0.f), &direction_);
	D3DXVec3Cross(&upDirection_, &direction_, &rightDir);

	deviceManager_->setViewSpace(position_, atPosition_, upDirection_);


	_mat matProjection;
	if (CAMERA_MODE::PERSPECTIVE == cameraMode_)
	{
		deviceManager_->setPerpectiveProjectionSpace(fovy_, screenWidth_ / screenHeight_, near_, far_);
	}
	else
	{
		deviceManager_->setOrthoProjectionSpace(screenWidth_, screenHeight_, near_, far_);
	}
}

void Camera::update()
{
	traceEntity();
	lockEntity();
	zoom();

	atPosition_ = position_ + direction_;

	deviceManager_->setViewSpace(position_, atPosition_, upDirection_);
	if (CAMERA_MODE::PERSPECTIVE == cameraMode_)
	{
		deviceManager_->setPerpectiveProjectionSpace(fovy_, screenWidth_ / screenHeight_, near_, far_);
	}
	else
	{
		deviceManager_->setOrthoProjectionSpace(screenWidth_, screenHeight_, near_, far_);
	}
}

void Camera::lateUpdate()
{
	
}

void Camera::render()
{
}

void Camera::release()
{
}

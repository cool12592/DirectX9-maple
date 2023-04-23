#pragma once
#include "ECS.h"
#include "DeviceManager.h"
class Camera :
	public Component
{
public:
	enum class CAMERA_MODE { PERSPECTIVE, ORTHOGONAL, CAMERA_MODE_END };
	enum class AXIS_TYPE { X_AXIS, Y_AXIS, Z_AXIS, AXIS_TYPE_END };
public:
	Camera(CAMERA_MODE cameraMode, _vec3 position, _vec3 direction, float screenWidth = SCREEN_WIDTH, float screenHeight = SCREEN_HEIGHT, float fovy = D3DX_PI / 4.f, float nearDistance = DEFAULT_NEAR_DISTANCE, float farDistance = DEFAULT_FAR_DISTANCE);
	virtual ~Camera();
public:
	HRESULT setPosition(_vec3 position);
	HRESULT rotateAxis(AXIS_TYPE axisType, float angle);
	HRESULT setCameraMode(CAMERA_MODE cameraMode, float nearDistance = DEFAULT_NEAR_DISTANCE, float farDistance = DEFAULT_FAR_DISTANCE);
	void setOnTrace(float xLimit, float yLimit);
	void setOffTrace() { onTrace_ = false; }
	void setOnLock(_vec2 leftLimit, _vec2  rightLimit);
	void setOffLock() { onTrace_ = false; }

	void setOnZoomIn(_vec3 targetCameraPosition, float zoomMagnification, float zoomSpeed, float zoomDuration);

	const _vec3& getPosition()const { return position_; }
private:
	void traceEntity();
	void lockEntity();
	void zoom();
public:
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
public:
	_vec3 position_;
	_vec3 direction_;
private:
	_vec3 atPosition_;
	_vec3 upDirection_;

	float fovy_;
	float near_, far_;
	float screenWidth_, screenHeight_;

	CAMERA_MODE cameraMode_ = CAMERA_MODE::PERSPECTIVE;
	DeviceManager* deviceManager_;

private:
	bool onTrace_ = false;
	float xLimit_ = 0.f;
	float yLimit_ = 0.f;

	bool onLock_ = false;
	_vec2 leftLimit_;
	_vec2 rightLimit_;

	bool onZoom_ = false;
	_vec3 originalPosition_;
	float originalScreenWidth_, originalScreenHeight_;

	_vec3 targetPosition_;
	float zoomScreenWidth_, zoomScreenHeight_;
	float lerpValue;
	float zoomSpeed_;
	float zoomDuration_;
	float zoomTimer_;
};
 

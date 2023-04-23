#include "stdafx.h"
#include "Ray.h"
#include "InputManager.h"
#include "DeviceManager.h"

Ray::Ray() :device_(DeviceManager::getInstance()->getDevice()), inputManager_(InputManager::getInstance()), origin_(_vec3(0.f, 0.f, 0.f)),direction_(_vec3(0.f,0.f,0.f))
{
}

Ray::~Ray()
{
}

bool Ray::rayCastCollider2D(const COLLIDERRECT2D & colliderRect)
{
	_vec3 lefttop = { colliderRect.left,colliderRect.top,0.f };
	_vec3 rightTop= { colliderRect.right,colliderRect.top,0.f };
	_vec3 leftBottom= { colliderRect.left,colliderRect.bottom,0.f };
	_vec3 rightBottom = { colliderRect.right,colliderRect.bottom,0.f };

	float u, v, dist;
	if (D3DXIntersectTri(&lefttop, &rightTop, &rightBottom, &origin_, &direction_, &u, &v, &dist) ||
		D3DXIntersectTri(&lefttop, &rightBottom, &leftBottom, &origin_, &direction_, &u, &v, &dist))
		return true;

	return false;
}

void Ray::initialize()
{
}

void Ray::update()
{
	updateRay();
}

void Ray::lateUpdate()
{
}

void Ray::render()
{
	
}

void Ray::release()
{
}

HRESULT Ray::updateRay()
{
	int mouseX, mouseY;
	D3DVIEWPORT9 viewport;
	_mat matView, matProj;
	_mat matInverseView;
	inputManager_->getMousePosition(mouseX, mouseY);

	device_->GetViewport(&viewport);
	device_->GetTransform(D3DTS_VIEW, &matView);
	device_->GetTransform(D3DTS_PROJECTION, &matProj);


	origin_ = _vec3(0.f, 0.f, 0.f);
	direction_.x = ((2.f*mouseX) / viewport.Width - 1.f) / matProj._11;
	direction_.y = ((-2.f*mouseY) / viewport.Height + 1.f) / matProj._22;
	direction_.z = 1.f;

	D3DXMatrixInverse(&matInverseView, 0, &matView);

	D3DXVec3TransformCoord(&origin_, &origin_, &matInverseView);
	D3DXVec3TransformNormal(&direction_, &direction_, &matInverseView);
	D3DXVec3Normalize(&direction_, &direction_);

	return S_OK;
}

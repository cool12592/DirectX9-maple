#include "stdafx.h"
#include "MapBasic.h"


void MapBasic::initialize()
{

	//entity->addComponent<Camera>(Camera::CAMERA_MODE::ORTHOGONAL, _vec3(0.f, 0.f, -1.f), _vec3(0.f, 0.f, 1.f));
}

void MapBasic::update()
{
	
	
	/*Camera& camera = entity->getComponent<Camera>();
if (Input.keyPressing(DIK_W))
	camera.position_.y += 5.f;
if (Input.keyPressing(DIK_S))
	camera.position_.y -= 5.f;
if (Input.keyPressing(DIK_A))
	camera.position_.x -= 5.f;
if (Input.keyPressing(DIK_D))
	camera.position_.x += 5.f;*/

	
	/*if (Input.keyDown(DIK_T))
		entity->setActive(false);*/
}

void MapBasic::lateUpdate()
{
}

void MapBasic::render()
{
}

void MapBasic::release()
{
}

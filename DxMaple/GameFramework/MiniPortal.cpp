#include "stdafx.h"
#include "MiniPortal.h"
#include "GameManager.h"
void MiniPortal::initialize()
{
	entity->addComponent<Transform>(_vec3(0.f,0.f,0.f) , _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));




	entity->addComponent<BoxCollider>(_vec3(10.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(50.f, 50.f, 50.f));
	entity->getComponent<BoxCollider>().bindColliderFunction(
		bind(&MiniPortal::enterCollider, this, placeholders::_1),
		bind(&MiniPortal::stayCollider, this, placeholders::_1),
		bind(&MiniPortal::exitCollider, this, placeholders::_1));





}

void MiniPortal::update()
{
	




}



void MiniPortal::lateUpdate()
{

}

void MiniPortal::render()
{
}

void MiniPortal::release()
{
}

void MiniPortal::playerTransmission()
{
	if(portalON)
	GameManager::getInstance()->getPlayer()->getComponent<Transform>().position_ = destination_;
}
